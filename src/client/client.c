/** Fichiers d'inclusion **/

#include "client.h"

/** Fonctions **/

void usage() { fprintf(stderr, "Syntax : client <host> <port>\n"); }

void gestion_sig()
{
    running = false;
    printf("\nBye !\n");
    sleep(1);
}

void demarrer_client_jeu(int* socket)
{
    char message[MAX_MESSAGE] = "Hello World!";
    // envoi_message_tcp(*socket, message, MAX_MESSAGE);
    envoi_message_udp(*socket, message, MAX_MESSAGE, "127.0.0.1", 9999);
}

/* Fonction principale */

int main(int argc, char* argv[])
{
    // Analyse des arguments
    if (argc != 3) {
        usage();
        exit(-1);
    }
    char* host = argv[1];
    char* port = argv[2];

    init_sig((void* (*)(void*))gestion_sig);

    // int socket = init_client_tcp(host, port);
    int socket = init_client_udp(host, port);
    creer_tache((void* (*)(void*))demarrer_client_jeu, (void*)&socket, sizeof(socket));

    getchar();

    return 0;
}
