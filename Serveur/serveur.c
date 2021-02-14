/**** Programme de creation de labyrinthe ****/

/** Fichiers d'inclusion **/

#include "libsig.h"

/** Fonctions **/

/* Fonction principale */

int main(void) {
    bool demarre = false;

    init_signaux();

    while (1) {
        if (demarre == false) {
            demarrer_serveur_jeu();
        } else {
            sleep(1);
        }
    }

    return 0;
}
