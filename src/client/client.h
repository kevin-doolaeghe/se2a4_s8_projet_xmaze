/**** Header client ****/

#ifndef _CLIENT_H_
#define _CLIENT_H_

/** Fichiers d'inclusion des bibliothèques **/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "libsig.h"
#include "libtcp.h"
#include "libthread.h"

/** Constantes **/

#define MAX_MESSAGE 30

/** Variables **/

static bool connecte;

/** Prototypes **/

int main(int argc, char* argv[]);
void loop();
void usage();
void demarrer_client_jeu(int* socket);

#endif
