/** Fichiers d'inclusion **/

#include "client.h"

/** Fonctions **/

void usage() { fprintf(stderr, "Syntax : client <host> <port>\n"); }

void gestion_sig()
{
    running = false;
    printf("\nBye !\n");
    sleep(1);
    exit(0);
}

void demarrer_client_jeu(int* socket)
{
    char message[MAX_MESSAGE] = "TCP message";
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

    init_sig((void* (*)(void*))gestion_sig);

    char message[MAX_MESSAGE] = "Broadcast UDP message";

    envoi_broadcast_udp(host, "255.255.255.0", port, message, MAX_MESSAGE);
    //envoi_message_udp(host, port, message, MAX_MESSAGE);

    //int socket = init_client_tcp(host, port);
    //creer_tache((void* (*)(void*))demarrer_client_jeu, (void*)&socket, sizeof(socket));

    pause();

    return 0;
}
