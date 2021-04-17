/**** Header graphiques UDP ****/

#ifndef _GRAPHIQUES_H_
#define _GRAPHIQUES_H_

/** Fichiers d'inclusion des bibliothèques **/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "libaffiche.h"
#include "libprotocole.h"
#include "libudp.h"

/** Variables **/

extern bool quitter_client;
extern bool partie_en_cours;

/** Prototypes **/

void tache_gestion_graphique(int* ecoute);
void reception_graphique_udp(char* message, int taille, char* ip);

#endif
