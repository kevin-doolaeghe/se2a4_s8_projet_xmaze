/**** Header client ****/

#ifndef _CLIENT_H_
#define _CLIENT_H_

/** Fichiers d'inclusion des bibliothèques **/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "libaffiche.h"
#include "libprotocole.h"
#include "libserveur.h"
#include "libserveurlist.h"
#include "libsig.h"
#include "libstrlist.h"
#include "libtcp.h"
#include "libthread.h"
#include "libudp.h"

/** Constantes **/

/** Variables **/

server_list_t serveur_list;
server_t serveur;

int id;

bool quitter_client;
bool partie_en_cours;

/** Prototypes **/

int main(int argc, char* argv[]);
void usage();
void init_client();
void detruire_client();

void connexion_chat(int id);
void tache_ecoute_chat(int* ecoute);
void reception_message_chat(char* message, int taille);
void envoi_message_chat(char* message);

void tache_diffusion_udp(int* ecoute);
void reception_diffusion_udp(char* message, int taille, char* ip);

void tache_touches_udp(int touche);

void tache_gestion_graphique(int* ecoute);
void reception_graphique_udp(char* message, int taille, char* ip);

void gestion_evenements();

void boucle_commande();

#endif
