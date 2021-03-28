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
#include "libudp.h"

/** Constantes **/

#define MAX_MESSAGE 30

/** Variables **/

bool running = true;

/** Prototypes **/

int main(int argc, char* argv[]);
void usage();
void gestion_sig();
void demarrer_client_jeu(int* socket);

#endif
