/**** Header client ****/

#ifndef _CLIENT_H_
#define _CLIENT_H_

/** Fichiers d'inclusion des bibliothèques **/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "libsig.h"

/** Constantes **/

/** Variables **/

static bool connecte;

/** Prototypes **/

int main(int argc,char *argv[]);

void usage();

#endif
