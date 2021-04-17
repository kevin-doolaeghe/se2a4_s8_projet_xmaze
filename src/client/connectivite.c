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
    if (size_of_server_list(&serveur_list) >= id && serveur.fd == -1) {
        pt_server_cell_t tmp = serveur_list;
        int current = 1;
        while (current != id)
            tmp = tmp->next;
        copy_server(&serveur, &(tmp->server));

        int chat_sock = init_client_tcp(to_cstr(&(serveur.ip)), PORT_CHAT_TCP);
        set_server_fd(&serveur, chat_sock);
        create_task((void* (*)(void*))thread_chat, (void*)&chat_sock, sizeof(chat_sock));

        unsigned char resultat = creerFenetre(LARGEUR, HAUTEUR, TITRE);
        if (!resultat) {
            fprintf(stderr, "Problème graphique !\n");
            exit(EXIT_FAILURE);
        }

        create_task((void* (*)(void*))thread_touches, NULL, 0);

        int graphique_sock = init_serveur_udp(PORT_GRAPHIQUE_UDP);
        create_task((void* (*)(void*))thread_graphique, (void*)&graphique_sock, sizeof(graphique_sock));
    }
}

void reception_message_chat(char* message, int taille)
{
#ifdef DEBUG
    printf("tcp_chat: message of %d bytes: %s\n", taille, message);
#endif
    printf("%s\n", message);
}

/**** Diffusion UDP ****/

void reception_identite(char* message, int taille, char* ip)
{
#ifdef DEBUG
    printf("udp_diffusion: message of %d bytes from %s: %s\n", taille, ip, message);
#endif

    if (sizeof(message) > sizeof(pr_udp_identite_t)) {
        pr_udp_identite_t trame;
        traduire_trame_identite(&trame, message, taille);

        server_t tmp;
        init_server(&tmp);

        set_server_id(&tmp, trame.id_serveur);
        set_server_ip(&tmp, ip);
        set_server_port_tcp(&tmp, trame.port_tcp);
        set_server_port_udp_touches(&tmp, trame.port_udp_touches);

        add_server_to_list(&serveur_list, &tmp);

        destroy_server(&tmp);
    }

    if (quitter_client == true)
        exit(EXIT_SUCCESS);
}

/**** Touche UDP ****/

void envoi_touche(int touche)
{
    pr_udp_touches_t trame;
    trame.id_client = id;
    trame.touches = touche;

    char message[sizeof(pr_udp_touches_t)];
    memcpy(message, &trame, sizeof(pr_udp_touches_t));

    envoi_message_udp(to_cstr(&(serveur.ip)), PORT_TOUCHES_UDP, message, sizeof(pr_udp_touches_t));
}

void gestion_evenements()
{
    int touche;
    unsigned char fenetre, quitter;
    while (1) {
        int evenement = attendreEvenement(&touche, &fenetre, &quitter);
        if (!evenement) {
            usleep(ATTENTE);
            continue;
        }

        if (quitter == 1) {
            break;
        }

        if (touche != 0 && touche != TOUCHE_AUTRE && serveur.fd != -1) {
#ifdef DEBUG
            printf("touche: %08x\n", touche);
#endif
            envoi_touche(touche);
        }
    }
    fermerFenetre();
    detruire_client();
}

/**** Graphique UDP ****/

void reception_graphique(char* message, int taille, char* ip)
{
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

    effacerFenetre();
    dessine_2D((objet2D*)trame.objets, trame.nb_objets);
    synchroniserFenetre();

    if (quitter_client == true)
        exit(EXIT_SUCCESS);
}
