/** Fichiers d'inclusion **/

#include "serveur.h"

/** Fonctions **/

void usage() { fprintf(stderr, "Syntax : server\n"); }

void gestion_sig()
{
    quitter_serveur = true;
    partie_en_cours = false;

    destroy_client_list(&client_list);

    printf("\nBye !\n");
    sleep(1);
    exit(0);
}

/** ------------------------------------------------- **/

void init_server()
{
    quitter_serveur = false;
    partie_en_cours = false;

    int chat_sock = init_serveur_tcp(PORT_CHAT_TCP);
    creer_tache((void* (*)(void*))demarrer_chat_tcp, (void*)&chat_sock, sizeof(chat_sock));

    creer_tache((void* (*)(void*))tache_diffusion_udp, NULL, 0);

    int touches_sock = init_serveur_udp(PORT_TOUCHES_UDP);
    creer_tache((void* (*)(void*))demarrer_touches_udp, (void*)&touches_sock, sizeof(touches_sock));

    creer_tache((void* (*)(void*))tache_graphique_udp, NULL, 0);
}

void gestion_client_chat_tcp(void* arg)
{
    int dialogue = *((int*)arg);
    creer_tache((void* (*)(void*))tache_chat_tcp, (void*)&dialogue, sizeof(dialogue));
}

/** ------------------------------------------------- **/

void tache_chat_tcp(int* s)
{
    int dialogue = *(int*)s;
    char tampon[MAX_TAMPON_TCP];
    int ret;

    client_t client;
    init_client(&client);

    char* ip = get_ip(*s);
    set_client_fd(&client, *s);
    set_client_ip(&client, ip);
    set_client_pseudo(&client, "pseudotest");

    append_client_to_list(&client_list, &client);

    while (quitter_serveur == false) {
        ret = lire_message_tcp(dialogue, tampon, MAX_TAMPON_TCP - 1);
        if (ret <= 0) {
            detruire_lien_tcp(dialogue);
            destroy_client(&client);
            client_count--;
            return;
        }
        tampon[ret] = 0;

        printf("chat_tcp: message from %s: %s\n", to_cstr(&client.ip), tampon);
        print_client_list(&client_list);
    }
}

void tache_diffusion_udp()
{
    while (partie_en_cours == false) {
        envoi_message_udp("127.0.0.1", PORT_DIFFUSION_UDP, "TRAME DIFF UDP\0", MAX_TAMPON_UDP);
        sleep(1);
    }
}

void tache_touches_udp(char* message, int* size, char* ip)
{
    printf("udp_touches: message of %d bytes from %s: %s\n", *size, ip, message);
}

void tache_graphique_udp()
{
    while (partie_en_cours == true) {
        pt_client_cell_t ptr = client_list;

        while (ptr != NULL) {
            envoi_message_udp(to_cstr(&(ptr->client.ip)), PORT_GRAPHIQUE_UDP, "TACHE GRAPH UDP\0", MAX_TAMPON_UDP);
            ptr = ptr->next;
        }
        sleep(1);
    }
}

/** ------------------------------------------------- **/

void demarrer_chat_tcp(int* s)
{
    boucle_serveur_tcp(*s, (void* (*)(void*))gestion_client_chat_tcp);
}

void demarrer_touches_udp(int* s)
{
    boucle_serveur_udp(*s, (void* (*)(void*, void*, void*))tache_touches_udp);
}

/** ------------------------------------------------- **/

/* Fonction principale */

int main(int argc, char* argv[])
{
    /*
    // Analyse des arguments
    if (argc != 2) {
        usage();
        exit(-1);
    }
    char* service = argv[1];
    */

    init_sig((void* (*)(void*))gestion_sig);

    init_server();

    pause();

    return 0;
}
