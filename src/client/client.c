/** Fichiers d'inclusion **/

#include "client.h"

/** Fonctions **/

void usage() { fprintf(stderr, "Syntax : client <arg>\n"); }

void loop()
{
    bool demarre = false;

    while (1) {
        if (demarre == false) {
            demarrer_client_jeu();
        } else {
            sleep(1);
        }
    }
}

void demarrer_client_jeu() {}

/* Fonction principale */

int main(int argc, char* argv[])
{
    // Analyse des arguments
    if (argc != 2) {
        usage();
        exit(-1);
    }
    char* port = argv[1];

    init_sig();

    return 0;
}
