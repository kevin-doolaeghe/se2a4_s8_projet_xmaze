/** Fichiers d'inclusion **/

#include "serveur.h"

/** Fonctions **/

void usage() { fprintf(stderr, "Syntaxe : ./serveur\n"); }

void init_serveur()
{
    init_sig((void* (*)(void*))detruire_serveur);

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
    usleep(100);
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
        sleep(1);
    }
}

/**** Touches UDP ****/

void tache_gestion_touches(int* ecoute)
{
    boucle_serveur_udp(*ecoute, (void* (*)(char*, int, char*))reception_touches_udp);
}

void reception_touches_udp(char* message, int taille, char* ip)
{
    printf("udp_touches: message of %d bytes from %s:", taille, ip);
    int i;
    for (i = 0; i < sizeof(message); i++)
        printf("%x", message[i]);
    printf("\n");
    if (quitter_serveur == true)
        exit(EXIT_SUCCESS);
}

/**** Graphiques UDP ****/

void tache_gestion_graphique()
{
    while (quitter_serveur == false) {
        if (partie_en_cours == true) {
            pt_client_cell_t ptr = client_list;

            while (ptr != NULL) {
                char message[MAX_TAMPON_UDP] = "TRAME GRAPH UDP";
                envoi_message_udp(to_cstr(&(ptr->client.ip)), PORT_GRAPHIQUE_UDP, message, MAX_TAMPON_UDP);
                ptr = ptr->next;
            }
        }
        sleep(1);
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
