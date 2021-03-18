/**** Header client ****/

#ifndef _CLIENT_H_
#define _CLIENT_H_

/** Fichiers d'inclusion des bibliothèques **/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "libsig.h"
#include "libthread.h"

/** Constantes **/

/** Variables **/

static bool connecte;

/** Prototypes **/

int main(int argc, char* argv[]);
void snippet();
void usage();

#endif
