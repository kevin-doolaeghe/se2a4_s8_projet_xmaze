/** Fichiers d'inclusion **/

#include "client.h"

/** Fonctions **/

void usage() {
    fprintf(stderr,"Syntax : client <arg>\n");
}

void demarrer_client_jeu() {

}

/* Fonction principale */

int main(int argc,char *argv[]) {
    if(argc != 2){
        usage();
        exit(-1);
    }
    char *port = argv[1];

    bool demarre = false;

    init_sig();

    while (1) {
        if (demarre == false) {
            demarrer_client_jeu();
        } else {
            sleep(1);
        }
    }

    return 0;
}
