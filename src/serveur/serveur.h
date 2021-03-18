/**** Header serveur ****/

#ifndef _SERVEUR_H_
#define _SERVEUR_H_

/** Fichiers d'inclusion des bibliothèques **/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "libsig.h"
#include "libthread.h"

/** Constantes **/

/** Variables **/

/** Prototypes **/

int main(int argc, char* argv[]);
void demarrer_serveur_jeu();
void usage();

#endif
