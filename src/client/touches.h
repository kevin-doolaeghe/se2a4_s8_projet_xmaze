/**** Header touches UDP ****/

#ifndef _TOUCHES_H_
#define _TOUCHES_H_

/** Fichiers d'inclusion des bibliothèques **/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "libaffiche.h"
#include "libprotocole.h"
#include "libserveur.h"
#include "libudp.h"

/** Variables **/

extern server_t serveur;

extern int id;

extern bool quitter_client;
extern bool partie_en_cours;

/** Prototypes **/

void gestion_evenements();
extern void detruire_client();

#endif
