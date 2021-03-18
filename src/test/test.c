/** Fichiers d'inclusion **/

#include "test.h"

/** Fonctions **/

void usage()
{
    fprintf(stderr, "Syntax : test <arg>\n");
}

void snippet()
{
    printf("hello");
    sleep(2);
}

/* Fonction principale */

int main(int argc, char* argv[])
{
    if (argc != 2) {
        usage();
        exit(-1);
    }
    char* port = argv[1];

    bool demarre = false;

    init_sig();

    while (1) {
        if (demarre == false) {
            //creer_tache(snippet, NULL, 0);
        } else {
            sleep(1);
        }
    }

    return 0;
}
