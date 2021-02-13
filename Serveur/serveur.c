/**** Programme de creation de labyrinthe ****/

/** Fichiers d'inclusion **/

#include "libsig.h"

/** Fonctions **/

/* Fonction principale */

int main(void) {
    bool demarre = false;

    init_sig();

    while (1) {
        if (demarre == false) {
            demarrer_jeu();
        } else {
            sleep(1);
        }
    }

    return 0;
}
