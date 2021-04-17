/**** Bibliotheque de threading ****/

#ifndef _LIBTHREAD_H_
#define _LIBTHREAD_H_

/** Fichiers d'inclusion des bibliotheques **/

#include <pthread.h>
#include <stdlib.h>
#include <string.h>

/** Constantes **/

#define MAX_MUTEX 100

/** Types **/

typedef struct func_arg_s func_arg_t;
struct func_arg_s {
    void* (*f)(void*);
    void* arg;
};

typedef struct func_arg2_s func_arg2_t;
struct func_arg2_s {
    void* (*f)(void*, void*);
    void* arg1;
    void* arg2;
};

/** Prototypes **/

void create_task(void* (*task)(void*), void* arg, int size);
void create_task2(void* (*task)(void*, void*), void* arg1, int size1, void* arg2, int size2);
void* func_gen(void* generic);
void* func_gen2(void* generic);
void init_mutex_list();
void p(int id);
void v(int id);

#endif
