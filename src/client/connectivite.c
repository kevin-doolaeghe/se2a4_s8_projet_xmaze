/** Fichiers d'inclusion **/

#include "connectivite.h"

/** Fonctions **/

/**** Taches ****/

void thread_chat(int* ecoute)
{
    boucle_reception_tcp(*ecoute, (void* (*)(char*, int))reception_message_chat);
}

void thread_diffusion(int* ecoute)
{
    boucle_serveur_udp(*ecoute, (void* (*)(char*, int, char*))reception_identite);
}

void thread_touches()
{
    gestion_evenements();
}

void thread_graphique(int* ecoute)
{
    boucle_serveur_udp(*ecoute, (void* (*)(char*, int, char*))reception_graphique);
}

/**** Chat TCP ****/

void connexion_chat(int id)
{
    if (search_server_in_list(&serveur_list, id) && serveur.fd == -1) {
        // Recuperation du serveur
        server_t *res = get_server_by_id(&serveur_list, id);
        copy_server(&serveur, res);

        // Demarrage de la tache de dialogue
        int chat_sock = init_client_tcp(to_cstr(&(serveur.ip)), serveur.port_tcp);
        set_server_fd(&serveur, chat_sock);
        create_task((void* (*)(void*))thread_chat, (void*)&chat_sock, sizeof(chat_sock));
    }
}

void reception_message_chat(char* message, int taille)
{
    // Traduction de la trame
    pr_tcp_chat_t trame;
    traduire_trame_chat(&trame, message, taille);

#ifdef DEBUG
    printf("Recieved message of %d bytes.\n", taille);
    printf("\tType: %d\n\tCommand: %d\n\tContent: %s\n", trame.id_client, trame.commande, trame.message);
#endif

    // Traitement du message recu
    switch (trame.commande) {
    case CMD_MESG_ID:
        printf("%s\n", trame.message);
        break;
    case CMD_IDTF_ID:
        id = atoi(trame.message);
        break;
    case CMD_STRT_ID:
        printf("Démarrage de la partie!\n");
        demarrer_partie();
        break;
    case CMD_STOP_ID:
        printf("Arrêt de la partie!\n");
        arreter_partie();
        break;
    default:
        break;
    }
}

void demarrer_partie()
{
    // Demarrage de la partie
    partie_en_cours = true;

    // Ouverture de la fenetre
    unsigned char resultat = creerFenetre(LARGEUR, HAUTEUR, TITRE);
    if (!resultat) {
        fprintf(stderr, "Problème graphique !\n");
        exit(EXIT_FAILURE);
    }

    // Demarrage de la tache d'envoi des touches
    create_task((void* (*)(void*))thread_touches, NULL, 0);

    // Demarrage de la tache de reception des objets graphiques
    int graphique_sock = init_serveur_udp(PORT_GRAPHIQUE_UDP);
    create_task((void* (*)(void*))thread_graphique, (void*)&graphique_sock, sizeof(graphique_sock));
}

void arreter_partie()
{
    // Arret de la partie
    partie_en_cours = false;

    usleep(ATTENTE);

    // Fermeture de la fenetre
    fermerFenetre();
}

/**** Diffusion UDP ****/

void reception_identite(char* message, int taille, char* ip)
{
    // Traduction de la trame
    pr_udp_identite_t trame;
    traduire_trame_identite(&trame, message, taille);

    #ifdef DEBUG
    printf("Recieved identity message: ");
    int i;
    for (i = 0; i < taille; i++)
        printf("%02x", message[i]);
    printf("\n");
    printf("Diffusion message of %d bytes recieved:\n", taille);
    printf("\tServer IP: %s\n", ip);
    printf("\tServer id: %d\n", trame.id_serveur);
    printf("\tChat port: %d\n", trame.port_tcp);
    printf("\tKey port: %d\n", trame.port_udp_touches);
    #endif

    server_t tmp;
    init_server(&tmp);

    // Recuperation des informations du serveur
    set_server_id(&tmp, trame.id_serveur);
    set_server_ip(&tmp, ip);
    set_server_port_tcp(&tmp, trame.port_tcp);
    set_server_port_udp_touches(&tmp, trame.port_udp_touches);

    // Ajout du serveur a la liste
    add_server_to_list(&serveur_list, &tmp);

    destroy_server(&tmp);

    if (quitter_client == true)
        exit(EXIT_SUCCESS);
}

/**** Touche UDP ****/

void envoi_touche(int touche)
{
#ifdef DEBUG
    printf("touche: %08x\n", touche);
#endif

    // Preparation de la trame
    pr_udp_touches_t trame;
    trame.id_client = id;
    trame.touches = touche;

    int taille = sizeof(pr_udp_touches_t);
    char message[taille];

    // Ecriture de la trame
    ecrire_trame_touches(&trame, message, taille);

    // Envoi de la trame
    envoi_message_udp(to_cstr(&(serveur.ip)), serveur.port_udp_touches, message, taille);
}

void gestion_evenements()
{
    int touche;
    unsigned char fenetre, quitter;
    while (partie_en_cours == true) {
        int evenement = attendreEvenement(&touche, &fenetre, &quitter);
        if (!evenement) {
            usleep(ATTENTE);
            continue;
        }

        if (quitter == 1)
            arreter_partie();

        if (touche != 0 && touche != TOUCHE_AUTRE && serveur.fd != -1)
            envoi_touche(touche);
    }
}

/**** Graphique UDP ****/

void reception_graphique(char* message, int taille, char* ip)
{
    // Traduction de la trame
    pr_udp_graph_t trame;
    traduire_trame_graphique(&trame, message, taille);

#ifdef DEBUG
    int i;
    printf("udp_graphique: message of %d bytes from %s.\n", taille, ip);
    printf("%d objets graphiques reçus:\n", trame.nb_objets);
    for (i = 0; i < taille; i++)
        printf("%02x", message[i]);
    printf("\n");
#endif

    // Affichage des objets graphiques
    effacerFenetre();
    dessine_2D((objet2D*)trame.objets, trame.nb_objets);
    synchroniserFenetre();

    if (quitter_client == true)
        exit(EXIT_SUCCESS);
}
