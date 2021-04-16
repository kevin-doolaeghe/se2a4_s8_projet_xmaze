/** Fichiers d'inclusion **/

#include "serveur.h"

/** Fonctions **/

void usage() { fprintf(stderr, "Syntaxe : ./serveur\n"); }

void init_serveur()
{
    init_sig((void* (*)(void*))detruire_serveur);

    nb = dessin_vers_murs(laby, murs);

    quitter_serveur = false;
    partie_en_cours = false;

    int chat_sock = init_serveur_tcp(PORT_CHAT_TCP);
    creer_tache((void* (*)(void*))tache_gestion_chat, (void*)&chat_sock, sizeof(chat_sock));

    creer_tache((void* (*)(void*))tache_diffusion_udp, NULL, 0);

    int touches_sock = init_serveur_udp(PORT_TOUCHES_UDP);
    creer_tache((void* (*)(void*))tache_gestion_touches, (void*)&touches_sock, sizeof(touches_sock));

    creer_tache((void* (*)(void*))tache_gestion_graphique, NULL, 0);
}

void detruire_serveur()
{
    quitter_serveur = true;
    partie_en_cours = false;

    destroy_client_list(&client_list);

    printf("\nBye !\n");
    usleep(ATTENTE);
    exit(EXIT_SUCCESS);
}

/** ------------------------------------------------- **/

/**** Chat TCP ****/

void tache_gestion_chat(int* dialogue)
{
    boucle_serveur_tcp(*dialogue, (void* (*)(int, char*))gestion_client);
}

void gestion_client(int dialogue, char* ip)
{
#ifdef DEBUG
    printf("Recieved TCP connection demmand from %s\n", ip);
#endif

    //char tampon[MAX_TAMPON_TCP];
    //int ret;

    client_t client;
    init_client(&client);

    /*
    ret = lire_message_tcp(dialogue, tampon, MAX_TAMPON_TCP);
    if (ret <= 0)
        return;
    */

    set_client_fd(&client, dialogue);
    set_client_ip(&client, ip);
    set_client_pseudo(&client, "pseudotest");
    pos_t pos = { LABY_X / 2 * MUR_TAILLE, 0, MUR_TAILLE, 0 };
    set_client_position(&client, &pos);

    append_client_to_list(&client_list, &client);
    print_client_list(&client_list);

    creer_tache((void* (*)(void*))tache_discussion_client, (void*)&dialogue, sizeof(dialogue));

    destroy_client(&client);
}

void tache_discussion_client(int* dialogue)
{
    boucle_reception_tcp(*dialogue, (void* (*)(char*, int))reception_message);

    delete_client_from_list(&client_list, *dialogue);
    print_client_list(&client_list);
}

void reception_message(char* message, int taille)
{
    printf("chat_tcp: message of %d bytes: %s\n", taille, message);

    pt_client_cell_t ptr = client_list;

    while (ptr != NULL) {
        envoi_message_tcp(ptr->client.fd, message, taille);
        ptr = ptr->next;
    }
}

/**** Diffusion UDP ****/

void tache_diffusion_udp()
{
    while (quitter_serveur == false) {
        if (partie_en_cours == false) {
            pr_udp_identite_t trame;
            trame.id_serveur = ID_SERVEUR;
            trame.port_tcp = atoi(PORT_CHAT_TCP);
            trame.port_udp_touches = atoi(PORT_TOUCHES_UDP);

            char message[sizeof(pr_udp_identite_t)];
            memcpy(message, &trame, sizeof(pr_udp_identite_t));

            envoi_message_udp(BROADCAST, PORT_DIFFUSION_UDP, message, sizeof(pr_udp_identite_t));
        }
        sleep(3);
    }
}

/**** Touches UDP ****/

void tache_gestion_touches(int* ecoute)
{
    boucle_serveur_udp(*ecoute, (void* (*)(char*, int, char*))reception_touches_udp);
}

void reception_touches_udp(char* message, int taille, char* ip)
{
#ifdef DEBUG
    printf("udp_touches: message of %d bytes from %s: ", taille, ip);
    int i;
    for (i = 0; i < sizeof(message); i++)
        printf("%08x", message[i]);
    printf("\n");
#endif

    pr_udp_touches_t* trame = (pr_udp_touches_t*)message;

    int touche = trame->touches;
    printf("touche: %d\n", touche);
    client_t* client = get_client_by_id(&client_list, trame->id_client);

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

/**** Graphiques UDP ****/

void tache_gestion_graphique()
{
    while (quitter_serveur == false) {
        //if (partie_en_cours == true) {
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

            int taille = sizeof(uint32_t) + no * sizeof(objet2D);

            char* message = malloc(taille);
            int i;
            for (i = 0; i < sizeof(uint32_t); i++)
                message[i] = (no >> (3 - i) * 8) & 0xFF;
            for (i = 0; i < no; i++)
                memcpy(message + sizeof(uint32_t) + i * sizeof(objet2D), &(objets[i]), sizeof(objet2D));

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
        //}
        usleep(ATTENTE_GRAPHIQUE);
    }
}

/** ------------------------------------------------- **/

/* Fonction principale */

int main(int argc, char* argv[])
{
    // Analyse des arguments
    if (argc != 1) {
        usage();
        exit(EXIT_FAILURE);
    }

    init_serveur();

    pause();

    return 0;
}
