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
#include "libprotocole.h"
#include "libsig.h"
#include "libstr.h"
#include "libtcp.h"
#include "libthread.h"
#include "libudp.h"

/** Constantes **/

/** Variables **/

bool quitter_serveur;
bool partie_en_cours;

client_list_t client_list;

/** Prototypes **/

int main(int argc, char* argv[]);
void usage();
void gestion_sig();
void init_server();

void gestion_client_chat_tcp(void* arg);

void tache_chat_tcp(int* s);
void tache_diffusion_udp();
void tache_touches_udp(char* message, int* size, char* ip);
void tache_graphique_udp();

void demarrer_chat_tcp(int* s);
void demarrer_touches_udp(int* s);

#endif
