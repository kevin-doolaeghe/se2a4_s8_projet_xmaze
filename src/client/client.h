/**** Header client ****/

#ifndef _CLIENT_H_
#define _CLIENT_H_

/** Fichiers d'inclusion des bibliothèques **/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "libsig.h"

/** Constantes **/

/** Variables **/

static bool connecte;

/** Prototypes **/

int main(int argc, char* argv[]);
void demarrer_client_jeu();
void usage();

#endif
