/**** Header serveur ****/

#ifndef _SERVEUR_H_
#define _SERVEUR_H_

/** Fichiers d'inclusion des bibliothèques **/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "libclient.h"
#include "libclientlist.h"
#include "libsig.h"
#include "libtcp.h"
#include "libthread.h"

/** Constantes **/

/** Variables **/

bool running = true;
client_list_t client_list;

/** Prototypes **/

int main(int argc, char* argv[]);
void usage();
void gestion_sig();
void tache_chat_tcp(void* arg);
void tache_diffusion_udp(void* arg);
void tache_touches_udp(void* arg);
void tache_graphique_udp(void* arg);
void gestion_client_chat_tcp(void* arg);
void demarrer_serveur_jeu();

#endif
