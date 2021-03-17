/**** Bibliotheque de threading ****/

#ifndef _LIBTHREAD_H_
#define _LIBTHREAD_H_

/** Fichiers d'inclusion des bibliothèques **/

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>

/** Constantes **/

/** Variables **/

typedef struct func_arg_s func_arg_t;
struct func_arg_s {
    void *(*f)(void *);
    void *arg;
};

pthread_mutex_t lock;

/** Prototypes **/

int creer_tache(void *(*traitement)(void *), void *arg, int taille);
void *func_gen(void *generic);
void p();
void v();

#endif
