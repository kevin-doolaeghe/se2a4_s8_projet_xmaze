/**** Bibliotheque pour la gestion des signaux ****/

#ifndef _LIBSIG_H_
#define _LIBSIG_H_

/** Fichiers d'inclusion des bibliotheques **/

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

/** Prototypes **/

void init_sig(void* (*task)(void*));
void handle_sig(int sig);

#endif
