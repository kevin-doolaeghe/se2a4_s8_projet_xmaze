/**** Programme de creation de labyrinthe ****/

/** Fichiers d'inclusion **/

#include "libsig.h"

/** Variables **/

static bool connecte;

/** Fonctions **/

void usage() {
    fprintf(stderr,"Syntax : server <port>\n");
}

int main(int argc,char *argv[]) {
    if(argc!=2){
        usage();
        exit(-1);
    }
    char *port=argv[1];

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
