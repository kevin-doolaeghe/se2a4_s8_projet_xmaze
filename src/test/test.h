/**** Header client ****/

#ifndef _TEST_H_
#define _TEST_H_

/** Fichiers d'inclusion des bibliothèques **/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "libclient.h"
#include "libclientlist.h"
#include "libsig.h"
#include "libstrlist.h"
#include "libtcp.h"
#include "libthread.h"

/** Constantes **/

/** Variables **/

client_list_t client_list;

/** Prototypes **/

int main(int argc, char* argv[]);
void usage();
void hello_world();

#endif
