/** Fichiers d'inclusion **/

#include "test.h"

/** Fonctions **/

void usage()
{
    fprintf(stderr, "Syntax : test <port>\n");
}

void hello_world()
{
    while (1) {
        printf("Hello World !\n");
        sleep(1);
    }
}

void lancer_serveur(int* ecoute)
{
    boucle_serveur_tcp(*ecoute, (void* (*)(void*))tache_chat_tcp);
}

/* Fonction principale */

int main(int argc, char* argv[])
{
    // Analyse des arguments
    if (argc != 2) {
        usage();
        exit(-1);
    }
    char* service = argv[1];

    init_sig();

    creer_tache((void* (*)(void*))hello_world, NULL, 0);

    int ecoute = init_serveur_tcp(service);
    creer_tache((void* (*)(void*))lancer_serveur, (void*)&ecoute, sizeof(ecoute));

    pause();

    return 0;
}
