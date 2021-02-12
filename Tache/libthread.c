#include "libthread.h"

/** Fonctions **/

int create_thread(void *(*traitement)(void *)) {
    pthread_t tid;
    pthread_init(&tid, NULL, traitement, (void *) NULL);
    pthread_join(tid, NULL);

    return tid;
}
