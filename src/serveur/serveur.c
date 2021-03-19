/** Fichiers d'inclusion **/

#include "serveur.h"

/** Fonctions **/

void usage() { fprintf(stderr, "Syntax : server <arg>\n"); }

void loop()
{
    bool demarre = false;

    while (1) {
        if (demarre == false) {
            demarrer_serveur_jeu();
        } else {
            sleep(1);
        }
    }
}

void demarrer_serveur_jeu() {}

/* Fonction principale */

int main(int argc, char* argv[])
{
    // Analyse des arguments
    if (argc != 2) {
        usage();
        exit(-1);
    }
    // char* service = argv[1];

    init_sig();

    loop();

    return 0;
}
