/** Fichiers d'inclusions **/

#include "libthread.h"

/** Fonctions **/

void creer_tache(void* (*traitement)(void*), void* arg, int taille)
{
    func_arg_t* fa;
    fa = malloc(sizeof(func_arg_t));
    fa->arg = malloc(taille);
    memcpy(fa->arg, arg, taille);
    fa->f = traitement;

    pthread_t tid;
    pthread_create(&tid, NULL, func_gen, (void*)fa);
    // pthread_join(tid, NULL);
}

void* func_gen(void* generic)
{
    func_arg_t* fa = (func_arg_t*)generic;

    fa->f(fa->arg);
    free(fa->arg);
    free(fa);

    return NULL;
}

void p()
{
    pthread_mutex_init(&lock, NULL);
    pthread_mutex_lock(&lock);
}

void v()
{
    pthread_mutex_unlock(&lock);
    pthread_mutex_destroy(&lock);
}