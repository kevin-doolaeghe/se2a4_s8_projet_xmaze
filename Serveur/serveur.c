/** Fichiers d'inclusion **/

#include "serveur.h"

/** Fonctions **/

/* Fonction principale */

int main(int argc,char *argv[]) {
	// Analyse des arguments
	if(argc!=2){
		fprintf(stderr,"Syntaxe : bridge <port>\n");
		exit(-1);
	}
	char *service=argv[1];

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
