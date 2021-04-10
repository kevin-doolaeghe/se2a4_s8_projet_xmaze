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

#define BROADCAST "127.0.0.1"

/** Variables **/

client_list_t client_list;

bool quitter_serveur;
bool partie_en_cours;

/** Prototypes **/

int main(int argc, char* argv[]);
void usage();
void init_serveur();
void detruire_serveur();

void tache_gestion_chat(int* dialogue);
void gestion_client(int dialogue, char* ip);
void tache_discussion_client(int* dialogue);
void reception_message(char* message, int taille);

void tache_diffusion_udp();

void tache_gestion_touches(int* ecoute);
void reception_touches_udp(char* message, int taille, char* ip);

void tache_gestion_graphique();

#endif
