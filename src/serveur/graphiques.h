/**** Header graphiques UDP ****/

#ifndef _GRAPHIQUES_H_
#define _GRAPHIQUES_H_

/** Fichiers d'inclusion des bibliothèques **/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "libaffiche.h"
#include "libclientlist.h"
#include "libprotocole.h"
#include "libudp.h"

/** Constantes **/

#define ATTENTE_GRAPHIQUE 50000

/** Variables **/

extern client_list_t client_list;

extern bool quitter_serveur;
extern bool partie_en_cours;

extern mur murs[(LABY_X + 1) * LABY_Y + (LABY_Y + 1) * LABY_X];
extern char* laby[2 * LABY_Y + 1];
extern int nb;

/** Prototypes **/

void tache_gestion_graphique();

#endif
