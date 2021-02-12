/**** Bibliotheque thread  ****/

#ifndef _LIBTHREAD_H_
#define _LIBTHREAD_H_

/** Fichiers d'inclusion des bibliothèques **/

#include <pthread.h>

/** Constantes **/


/** Variables **/


/** Prototypes **/

int creer_tache(void *(*traitement)(void *));

void *tache_diffusion_udp(void *arg);

void *tache_chat_tcp(void *arg);

void *tache_touches_udp(void *arg);

void *tache_graphique_udp(void *arg);

#endif
