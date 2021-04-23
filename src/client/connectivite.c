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
        id = trame.id_client;
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

/**** Diffusion UDP ****/

void reception_identite(char* message, int taille, char* ip)
{
    if (quitter_client == false) {
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
    }
}

/**** Touche UDP ****/

void envoi_touche(int touche)
{
#ifdef DEBUG
    printf("key: %08x\n", touche);
#endif

    // Preparation de la trame
    pr_udp_touches_t trame;
    trame.id_client = id;
    trame.touches = touche;

    int taille = sizeof(pr_udp_touches_t);
    char message[taille];

    // Ecriture de la trame
    ecrire_trame_touches(&trame, message, taille);

    // Recuperation du port
    char port[MAX_PORT_LEN];
    sprintf(port, "%d", serveur.port_udp_touches);

    // Envoi de la trame
    envoi_message_udp(to_cstr(&(serveur.ip)), port, message, taille);
}

void gestion_evenements()
{
    int touche = TOUCHE_AUTRE;
    unsigned char fenetre, quitter;
    while (partie_en_cours == true) {
        int evenement = attendreEvenement(&touche, &fenetre, &quitter);
        if (!evenement) {
            usleep(ATTENTE);
            continue;
        }

        if (quitter == 1) {
            printf("Déconnexion du serveur..\n");
            deconnexion_serveur();
            break;
        }

        if (touche != 0 && touche != TOUCHE_AUTRE)
            envoi_touche(touche);
    }
}

/**** Graphique UDP ****/

void reception_graphique(char* message, int taille, char* ip)
{
    if (partie_en_cours == true) {
        // Traduction de la trame
        pr_udp_graph_t trame;
        traduire_trame_graphique(&trame, message, taille);

#ifdef DEBUG
        int i;
        printf("Recieved graphic packet of %d bytes from %s.\n", taille, ip);
        printf("%d graphic objects recieved:\n", trame.nb_objets);
        for (i = 0; i < taille; i++)
            printf("%02x", message[i]);
        printf("\n");
#endif

        // Affichage des objets graphiques
        effacerFenetre();
        dessine_2D((objet2D*)trame.objets, trame.nb_objets);
        synchroniserFenetre();
    }
}
