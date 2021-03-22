/** Fichiers d'inclusion **/

#include "serveur.h"

/** Fonctions **/

void usage() { fprintf(stderr, "Syntax : server <port>\n"); }

void gestion_sig()
{
    running = false;
    printf("\nBye !\n");
    sleep(1);
}

void tache_chat_tcp(void* arg)
{
    int dialogue = *(int*)arg;
    char tampon[MAX_TAMPON];
    int ret;

    while ((ret = lire_message_tcp(dialogue, tampon, MAX_TAMPON - 1)) > 0) {
        if (ret <= 0) {
            detruire_lien_tcp(dialogue);
            client_count--;
            return;
        }
        tampon[ret] = 0;
        printf("tampon: %s\n", tampon);
        print_client_list(&client_list);
    }
}

void tache_diffusion_udp(void* arg)
{
}

void tache_touches_udp(void* arg)
{
}

void tache_graphique_udp(void* arg)
{
}

void gestion_client_chat_tcp(void* arg)
{
    int dialogue = *((int*)arg);
    creer_tache((void* (*)(void*))tache_chat_tcp, (void*)&dialogue, sizeof(dialogue));
}

void demarrer_serveur_jeu(int* ecoute)
{
    boucle_serveur_tcp(*ecoute, (void* (*)(void*))gestion_client_chat_tcp);
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

    init_sig((void* (*)(void*))gestion_sig);

    int ecoute = init_serveur_tcp(service);
    creer_tache((void* (*)(void*))demarrer_serveur_jeu, (void*)&ecoute, sizeof(ecoute));

    pause();

    return 0;
}
