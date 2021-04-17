/**** Header touches UDP ****/

#ifndef _TOUCHES_H_
#define _TOUCHES_H_

/** Fichiers d'inclusion des bibliothèques **/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "libaffiche.h"
#include "libclientlist.h"
#include "libprotocole.h"
#include "libudp.h"

/** Variables **/

extern client_list_t client_list;

extern bool quitter_serveur;
extern bool partie_en_cours;

/** Prototypes **/

void tache_gestion_touches(int* ecoute);
void reception_touches_udp(char* message, int taille, char* ip);

#endif
