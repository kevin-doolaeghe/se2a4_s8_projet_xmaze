/**** Header client ****/

#ifndef _TEST_H_
#define _TEST_H_

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

static bool connecte;

/** Prototypes **/

int main(int argc, char* argv[]);
void usage();
void loop();
void snippet();

#endif
