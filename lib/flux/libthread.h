/**** Bibliotheque de threading ****/

#ifndef _LIBTHREAD_H_
#define _LIBTHREAD_H_

/** Fichiers d'inclusion des bibliothèques **/

#include <pthread.h>
#include <stdlib.h>
#include <string.h>

/** Constantes **/

#define MAX_MUTEX 100

/** Variables **/

typedef struct func_arg_s func_arg_t;
struct func_arg_s {
    void* (*f)(void*);
    void* arg;
};

pthread_mutex_t lock[MAX_MUTEX];

/** Prototypes **/

void create_task(void* (*task)(void*), void* arg, int size);
void* func_gen(void* generic);
void init_mutex_list();
void p(int id);
void v(int id);

#endif
