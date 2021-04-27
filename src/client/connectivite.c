/** Fichiers d'inclusion **/

#include "connectivite.h"

/** Fonctions **/

/**** Taches ****/

void thread_chat(int* ecoute)
{
    boucle_reception_tcp(*ecoute, (void* (*)(char*, int))reception_message_chat);
    if (connecte_au_serveur == true)
        deconnexion_serveur();
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
    printf("\tID: %d\n\tCommand: %d\n\tContent: %s\n", trame.id_client, trame.commande, trame.message);
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
        demarrer_jeu();
        break;
    case CMD_STOP_ID:
        arreter_jeu();
        break;
    case CMD_DISC_ID:
        if (trame.id_client == id)
            deconnexion_serveur();
        break;
    default:
        break;
    }
}

void envoi_trame_chat(int dialogue, int id, int commande)
{
    // Preparation de la trame
    pr_tcp_chat_t trame;
    trame.id_client = id;
    trame.commande = commande;
    trame.message = NULL;

    int taille = sizeof(trame.id_client) + sizeof(trame.commande);
    char message[taille];

    // Ecriture de la trame
    ecrire_trame_chat(&trame, message, taille);

    // Envoi de la trame
    envoi_message_tcp(dialogue, message, taille);
}

/**** Diffusion UDP ****/

void reception_identite(char* message, int taille, char* ip)
{
    if (quitter_client == false) {
        if (connecte_au_serveur == false) {
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
            add_server_to_list(&liste_serveur, &tmp);

            destroy_server(&tmp);
        } else {
            destroy_server_list(&liste_serveur);
        }
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
            envoi_trame_chat(serveur.fd, id, CMD_DISC_ID);
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
        printf("Recieved graphic packet of %d bytes from %s.\n", taille, ip);
#endif

        // Affichage des objets graphiques
        effacerFenetre();
        dessine_2D((objet2D*)trame.objets, trame.nb_objets);
        synchroniserFenetre();
    }
}
