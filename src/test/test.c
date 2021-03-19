/** Fichiers d'inclusion **/

#include "test.h"

/** Fonctions **/

void usage()
{
    fprintf(stderr, "Syntax : test <arg>\n");
}

void loop()
{
    bool demarre = false;

    while (1) {
        if (demarre == false) {
            //int a = 4;
            //creer_tache((void* (*)(void*))snippet, (void*)a, sizeof(a));
        } else {
            sleep(1);
        }
    }
}

void snippet(int a)
{
    printf("hello a=%i\n", a);
    sleep(2);
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

    int ecoute = init_serveur_tcp(service, 1);
    boucle_serveur_tcp(ecoute, snippet);

    return 0;
}
