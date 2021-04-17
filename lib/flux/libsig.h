/**** Bibliotheque pour la gestion des signaux ****/

#ifndef _LIBSIG_H_
#define _LIBSIG_H_

/** Fichiers d'inclusion des bibliothèques **/

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

/** Variables **/

struct sigaction action_sig;
void* (*handle_sig_func)(void*);

/** Prototypes **/

void init_sig(void* (*task)(void*));
void handle_sig(int sig);

#endif
