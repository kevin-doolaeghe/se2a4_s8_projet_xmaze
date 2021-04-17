/**** Header diffusion UDP ****/

#ifndef _DIFFUSION_H_
#define _DIFFUSION_H_

/** Fichiers d'inclusion des bibliothèques **/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "libprotocole.h"
#include "libserveur.h"
#include "libserveurlist.h"
#include "libudp.h"

/** Variables **/

extern server_list_t serveur_list;
extern server_t serveur;

extern int id;

extern bool quitter_client;
extern bool partie_en_cours;

/** Prototypes **/

void tache_diffusion_udp(int* ecoute);
void reception_diffusion_udp(char* message, int taille, char* ip);

#endif
