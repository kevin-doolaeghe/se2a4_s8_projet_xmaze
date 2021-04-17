/** Fichiers d'inclusion **/

#include "client.h"

/** Fonctions **/

void usage() { fprintf(stderr, "Syntaxe : ./client\n"); }

/** ------------------------------------------------- **/

void init_client()
{
    init_sig((void* (*)(void*))detruire_client);

    init_server(&serveur);

    unsigned char resultat = creerFenetre(LARGEUR, HAUTEUR, TITRE);
    if (!resultat) {
        fprintf(stderr, "Problème graphique !\n");
        exit(EXIT_FAILURE);
    }

    effacerFenetre();
    synchroniserFenetre();

    quitter_client = false;
    partie_en_cours = false;

    int diffusion_sock = init_serveur_udp(PORT_DIFFUSION_UDP);
    create_task((void* (*)(void*))tache_diffusion_udp, (void*)&diffusion_sock, sizeof(diffusion_sock));

    create_task((void* (*)(void*))gestion_evenements, NULL, 0);
}

void detruire_client()
{
    quitter_client = true;
    partie_en_cours = false;

    fermerFenetre();

    destroy_server_list(&serveur_list);
    destroy_server(&serveur);

    printf("\nBye !\n");
    usleep(ATTENTE);
    exit(EXIT_SUCCESS);
}

/* Fonction principale */

int main(int argc, char* argv[])
{
    // Analyse des arguments
    if (argc != 1) {
        usage();
        exit(EXIT_FAILURE);
    }

    init_client();

    boucle_commande();

    pause();

    return 0;
}
