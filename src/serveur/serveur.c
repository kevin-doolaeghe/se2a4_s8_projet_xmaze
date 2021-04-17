/** Fichiers d'inclusion **/

#include "serveur.h"

/** Fonctions **/

void usage() { fprintf(stderr, "Syntaxe : ./serveur\n"); }

void init_serveur()
{
    init_sig((void* (*)(void*))detruire_serveur);

    nb = dessin_vers_murs(laby, murs);

    quitter_serveur = false;
    partie_en_cours = false;

    int chat_sock = init_serveur_tcp(PORT_CHAT_TCP);
    create_task((void* (*)(void*))tache_gestion_chat, (void*)&chat_sock, sizeof(chat_sock));

    create_task((void* (*)(void*))tache_diffusion_udp, NULL, 0);

    int touches_sock = init_serveur_udp(PORT_TOUCHES_UDP);
    create_task((void* (*)(void*))tache_gestion_touches, (void*)&touches_sock, sizeof(touches_sock));

    create_task((void* (*)(void*))tache_gestion_graphique, NULL, 0);
}

void detruire_serveur()
{
    quitter_serveur = true;
    partie_en_cours = false;

    destroy_client_list(&client_list);

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

    init_serveur();

    pause();

    return 0;
}
