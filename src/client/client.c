/** Fichiers d'inclusion **/

#include "client.h"

/** Fonctions **/

void usage() { fprintf(stderr, "Syntax : client <host> <port>\n"); }

void demarrer_client_jeu(int* socket)
{
    char message[MAX_MESSAGE] = "Hello World!";
    envoi_message_tcp(*socket, message, MAX_MESSAGE);
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

    init_sig();

    int socket = init_client_tcp(host, port);
    creer_tache((void* (*)(void*))demarrer_client_jeu, (void*)&socket, sizeof(socket));

    getchar();

    return 0;
}
