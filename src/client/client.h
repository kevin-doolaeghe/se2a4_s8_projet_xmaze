/**** Header client ****/

#ifndef _CLIENT_H_
#define _CLIENT_H_

/** Fichiers d'inclusion des bibliothèques **/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "libprotocole.h"
#include "libserveur.h"
#include "libserveurlist.h"
#include "libsig.h"
#include "libtcp.h"
#include "libthread.h"
#include "libudp.h"

/** Constantes **/

#define HOST "127.0.0.1"

/** Variables **/

char* hote;
server_list_t serveur_list;
server_t serveur;

bool quitter_client;
bool partie_en_cours;

/** Prototypes **/

int main(int argc, char* argv[]);
void usage();
void init_client();
void detruire_client();

void tache_ecoute_chat(int* ecoute);
void reception_message(char* message, int taille);
void envoi_message();

void tache_diffusion_udp(int* ecoute);
void reception_diffusion_udp(char* message, int taille, char* ip);

void tache_touches_udp();

void tache_gestion_graphique(int* ecoute);
void reception_graphique_udp(char* message, int taille, char* ip);

#endif
