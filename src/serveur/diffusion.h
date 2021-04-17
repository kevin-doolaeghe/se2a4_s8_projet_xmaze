/**** Header diffusion UDP ****/

#ifndef _DIFFUSION_H_
#define _DIFFUSION_H_

/** Fichiers d'inclusion des bibliothèques **/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "libclientlist.h"
#include "libprotocole.h"
#include "libudp.h"

/** Constantes **/

#define ID_SERVEUR 34567

/** Variables **/

extern client_list_t client_list;

extern bool quitter_serveur;
extern bool partie_en_cours;

/** Prototypes **/

void tache_diffusion_udp();

#endif
