/** Fichiers d'inclusions **/

#include "libthread.h"

/** Fonctions **/

void create_task(void* (*task)(void*), void* arg, int size)
{
    func_arg_t* fa;
    fa = malloc(sizeof(func_arg_t));
    fa->arg = malloc(size);
    memcpy(fa->arg, arg, size);
    fa->f = task;

    pthread_t tid;
    pthread_create(&tid, NULL, func_gen, (void*)fa);
    pthread_detach(tid);
}

void* func_gen(void* generic)
{
    func_arg_t* fa = (func_arg_t*)generic;

    fa->f(fa->arg);
    free(fa->arg);
    free(fa);

    return NULL;
}

void init_mutex_list()
{
    int id;
    for (id = 0; id < MAX_MUTEX; id++) {
        pthread_mutex_init(&lock[id], NULL);
    }
}

void p(int id)
{
    pthread_mutex_lock(&lock[id]);
}

void v(int id)
{
    pthread_mutex_unlock(&lock[id]);
}