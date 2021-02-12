#include "libthread.h"

/** Fonctions **/

int creer_tache(void *(*traitement)(void *)) {
    pthread_t tid;
    pthread_init(&tid, NULL, traitement, (void *) NULL);
    pthread_join(tid, NULL);

    return tid;
}

void *tache_diffusion_udp(void *arg) {
    int status;

    pthread_exit((void *) &status);
}

void *tache_chat_tcp(void *arg) {
    int status;

    pthread_exit((void *) &status);
}

void *tache_touches_udp(void *arg) {
    int status;

    pthread_exit((void *) &status);
}

void *tache_graphique_udp(void *arg) {
    int status;

    pthread_exit((void *) &status);
}
