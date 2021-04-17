/** Fichiers d'inclusions **/

#include "libthread.h"

/** Variables **/

pthread_mutex_t lock[MAX_MUTEX];

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

void create_task2(void* (*task)(void*, void*), void* arg1, int size1, void* arg2, int size2)
{
    func_arg2_t* fa;
    fa = malloc(sizeof(func_arg2_t));
    fa->arg1 = malloc(size1);
    fa->arg2 = malloc(size2);
    memcpy(fa->arg1, arg1, size1);
    memcpy(fa->arg2, arg2, size2);
    fa->f = task;

    pthread_t tid;
    pthread_create(&tid, NULL, func_gen2, (void*)fa);
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

void* func_gen2(void* generic)
{
    func_arg2_t* fa = (func_arg2_t*)generic;

    fa->f(fa->arg1, fa->arg2);
    free(fa->arg1);
    free(fa->arg2);
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