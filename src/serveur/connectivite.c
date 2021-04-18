/** Fichiers d'inclusion **/

#include "connectivite.h"

/** Variables **/

mur murs[(LABY_X + 1) * LABY_Y + (LABY_Y + 1) * LABY_X];

char* laby[2 * LABY_Y + 1] = {
    " - - - - - - - - ",
    "|. . . . . . . .|",
    "                 ",
    "|. .|. . . . . .|",
    "       - -       ",
    "|. .|.|. .|. . .|",
    "                 ",
    "|. .|.|. .|. . .|",
    "                 ",
    "|. .|.|. .|. . .|",
    "       - -       ",
    "|. .|.|. . . . .|",
    "                 ",
    "|. .|.|. . . . .|",
    "                 ",
    "|. . . . . . . .|",
    " - - - - - - - - "
};

/** Fonctions **/

/**** Taches ****/

void thread_chat_connexion(int* dialogue)
{
    boucle_serveur_tcp(*dialogue, (void* (*)(int, char*))gestion_client);
}

void thread_chat_dialogue(int* dialogue)
{
    boucle_reception_tcp(*dialogue, (void* (*)(char*, int))reception_message);

    delete_client_from_list(&client_list, *dialogue);
    print_client_list(&client_list);
}

void thread_diffusion()
{
    diffuser_identite();
}

void thread_touches(int* ecoute)
{
    boucle_serveur_udp(*ecoute, (void* (*)(char*, int, char*))reception_touche);
}

void thread_graphique()
{
    calcul_graphique();
}

/**** Chat TCP ****/

void gestion_client(int dialogue, char* ip)
{
#ifdef DEBUG
    printf("Recieved TCP connection demmand from %s\n", ip);
#endif

    create_task((void* (*)(void*))thread_chat_dialogue, (void*)&dialogue, sizeof(dialogue));

    client_t client;
    init_client(&client);

    set_client_fd(&client, dialogue);
    set_client_ip(&client, ip);
    pos_t pos = { LABY_X / 2 * MUR_TAILLE, 0, MUR_TAILLE, 0 };
    set_client_position(&client, &pos);

    append_client_to_list(&client_list, &client);
    print_client_list(&client_list);

    destroy_client(&client);
}

void reception_message(char* message, int taille)
{
    pr_tcp_chat_t trame;
    traduire_trame_chat(&trame, message, taille);

#ifdef DEBUG
    printf("Recieved message of %d bytes.\n", taille);
    printf("\tType: %d\n\tCommand: %d\n\tContent: %s\n", trame.id_client, trame.commande, trame.message);
#endif

    pt_client_cell_t ptr = client_list;
    client_t* client;

    switch (trame.commande) {
    case CMD_MESG_ID:
        while (ptr != NULL) {
            envoi_message_tcp(ptr->client.fd, message, taille);
            ptr = ptr->next;
        }
        break;
    case CMD_NICK_ID:
        client = get_client_by_id(&client_list, trame.id_client);
        set_client_pseudo(client, trame.message);
        print_client_list(&client_list);
        break;
    case CMD_STRT_ID:
        partie_en_cours = true;

        while (ptr != NULL) {
            envoi_message_tcp(ptr->client.fd, message, taille);
            ptr = ptr->next;
        }
        break;
    case CMD_STOP_ID:
        partie_en_cours = false;

        while (ptr != NULL) {
            envoi_message_tcp(ptr->client.fd, message, taille);
            ptr = ptr->next;
        }
        break;
    default:
        break;
    }
}

/**** Diffusion UDP ****/

void diffuser_identite()
{
    while (quitter_serveur == false) {
        if (partie_en_cours == false) {
            pr_udp_identite_t trame;
            trame.id_serveur = ID_SERVEUR;
            trame.port_tcp = atoi(PORT_CHAT_TCP);
            trame.port_udp_touches = atoi(PORT_TOUCHES_UDP);

            char message[sizeof(pr_udp_identite_t)];
            memcpy(&trame, message, sizeof(pr_udp_identite_t));

            envoi_message_udp(BROADCAST, PORT_DIFFUSION_UDP, message, sizeof(pr_udp_identite_t));
        }
        sleep(3);
    }
}

/**** Touches UDP ****/

void reception_touche(char* message, int taille, char* ip)
{
    if (partie_en_cours == true) {
        pr_udp_touches_t trame;
        traduire_trame_touches(&trame, message, taille);

        int touche = trame.touches;

#ifdef DEBUG
        printf("udp_touches: message of %d bytes from %s: ", taille, ip);
        int i;
        for (i = 0; i < sizeof(message); i++)
            printf("%08x", message[i]);
        printf("\n");
        printf("touche: %d\n", touche);
#endif

        client_t* client = get_client_by_id(&client_list, trame.id_client);

        if (touche == TOUCHE_DROITE)
            client->position.angle += 10;
        if (touche == TOUCHE_GAUCHE)
            client->position.angle -= 10;
        if (client->position.angle < 0 || client->position.angle > 360)
            client->position.angle = client->position.angle % 360;
        if (touche == TOUCHE_HAUT) {
            client->position.x += MUR_TAILLE / 10 * sin(2 * M_PI * client->position.angle / 360);
            client->position.z += MUR_TAILLE / 10 * cos(2 * M_PI * client->position.angle / 360);
        }
        if (touche == TOUCHE_BAS) {
            client->position.x -= MUR_TAILLE / 10 * sin(2 * M_PI * client->position.angle / 360);
            client->position.z -= MUR_TAILLE / 10 * cos(2 * M_PI * client->position.angle / 360);
        }

        if (quitter_serveur == true)
            exit(EXIT_SUCCESS);
    }
}

/**** Graphiques UDP ****/

void calcul_graphique()
{
    int nb = dessin_vers_murs(laby, murs);
    while (quitter_serveur == false) {
        if (partie_en_cours == true) {
            pt_client_cell_t ptr = client_list;

            while (ptr != NULL) {
                point p = { ptr->client.position.x, ptr->client.position.y, ptr->client.position.z };
                int angle = ptr->client.position.angle;

                mur* m2 = duplique_murs(murs, nb);
                decale_murs(m2, nb, p);
                rotation_murs(m2, nb, angle);
                tri_murs(m2, nb);
                objet2D* objets = malloc(nb * sizeof(objet2D));
                int no;
                projete_murs(m2, nb, objets, &no);

                int taille = sizeof(int) + no * sizeof(objet2D);

                char* message = malloc(taille);
                int i;
                for (i = 0; i < sizeof(int); i++)
                    message[i] = (no >> (3 - i) * 8) & 0xFF;
                for (i = 0; i < no; i++)
                    memcpy(message + sizeof(int) + i * sizeof(objet2D), &(objets[i]), sizeof(objet2D));

#ifdef DEBUG
                printf("Sending graphic of %d bytes: ", taille);
                for (i = 0; i < taille; i++)
                    printf("%02x", message[i]);
                printf("\n");
#endif

                envoi_message_udp(to_cstr(&(ptr->client.ip)), PORT_GRAPHIQUE_UDP, message, taille);

                free(message);
                free(m2);
                free(objets);

                ptr = ptr->next;
            }
        }
        usleep(5 * ATTENTE);
    }
}
