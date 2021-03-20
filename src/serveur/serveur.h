/**** Header serveur ****/

#ifndef _SERVEUR_H_
#define _SERVEUR_H_

/** Fichiers d'inclusion des bibliothèques **/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "libsig.h"
#include "libtcp.h"
#include "libthread.h"

/** Constantes **/

/** Variables **/

/** Prototypes **/

int main(int argc, char* argv[]);
void usage();
void loop();
void demarrer_serveur_jeu();

#endif
