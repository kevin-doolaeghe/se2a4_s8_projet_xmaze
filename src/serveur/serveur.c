/** Fichiers d'inclusion **/

#include "serveur.h"

/** Fonctions **/

void usage() { fprintf(stderr, "Syntaxe : ./serveur\n"); }

void init_serveur()
{
    // Initialisation des signaux et des semaphores
    init_sig((void* (*)(void*))detruire_serveur);
    init_mutex_list();

    // Initialisation des variables
    p(MUTEX_QUIT);
    quitter_serveur = false;
    v(MUTEX_QUIT);
    p(MUTEX_PLAY);
    partie_en_cours = false;
    v(MUTEX_PLAY);

    // Demarrage des taches
    int chat_sock = init_serveur_tcp(PORT_CHAT_TCP);
    create_task((void* (*)(void*))thread_chat_connexion, (void*)&chat_sock, sizeof(chat_sock));

    create_task((void* (*)(void*))thread_diffusion, NULL, 0);

    int touches_sock = init_serveur_udp(PORT_TOUCHES_UDP);
    create_task((void* (*)(void*))thread_touches, (void*)&touches_sock, sizeof(touches_sock));

    create_task((void* (*)(void*))thread_graphique, NULL, 0);
}

void detruire_serveur()
{
    // Arret de la partie
    if (partie_en_cours == true)
        arreter_partie();

    // Arret du serveur
    p(MUTEX_QUIT);
    quitter_serveur = true;
    v(MUTEX_QUIT);

    // Nettoyage
    p(MUTEX_LIST);
    destroy_client_list(&client_list);
    v(MUTEX_LIST);

    // Delai d'attente
    printf("\nBye !\n");
    usleep(ATTENTE);
    exit(EXIT_SUCCESS);
}

void demarrer_partie()
{
    printf("Début de la partie.\n");

    pos_t pos = { LABY_X / 2 * MUR_TAILLE, 0, MUR_TAILLE, 0 };

    p(MUTEX_LIST);
    pt_client_cell_t ptr = client_list;
    while (ptr != NULL) {
        set_client_position(&(ptr->client), &pos);
        envoi_trame_chat(ptr->client.fd, ptr->client.id, CMD_STRT_ID);

        ptr = ptr->next;
    }
    v(MUTEX_LIST);

    partie_en_cours = true;
}

void arreter_partie()
{
    printf("Fin de la partie.\n");

    p(MUTEX_LIST);
    pt_client_cell_t ptr = client_list;
    while (ptr != NULL) {
        envoi_trame_chat(ptr->client.fd, ptr->client.id, CMD_STOP_ID);

        ptr = ptr->next;
    }
    v(MUTEX_LIST);

    partie_en_cours = false;
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
