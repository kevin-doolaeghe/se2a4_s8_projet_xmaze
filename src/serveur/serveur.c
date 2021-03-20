/** Fichiers d'inclusion **/

#include "serveur.h"

/** Fonctions **/

void usage() { fprintf(stderr, "Syntax : server <port>\n"); }

void loop()
{
    bool demarre = false;

    while (1) {
        if (demarre == false) {

        } else {
            sleep(1);
        }
    }
}

void demarrer_serveur_jeu(int* ecoute)
{
    boucle_serveur_tcp(*ecoute, tache_chat_tcp);
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

    int ecoute = init_serveur_tcp(service);
    creer_tache((void* (*)(void*))demarrer_serveur_jeu, (void*)&ecoute, sizeof(ecoute));

    pause();

    return 0;
}
