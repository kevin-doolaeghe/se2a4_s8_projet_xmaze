/**** Header client ****/

#ifndef _CLIENT_H_
#define _CLIENT_H_

/** Fichiers d'inclusion des bibliothèques **/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "chat.h"
#include "diffusion.h"
#include "libaffiche.h"
#include "libserveur.h"
#include "libserveurlist.h"
#include "libsig.h"
#include "libthread.h"
#include "shell.h"
#include "touches.h"

/** Variables **/

server_list_t serveur_list;
server_t serveur;

int id;

bool quitter_client;
bool partie_en_cours;

/** Prototypes **/

int main(int argc, char* argv[]);
void usage();
void init_client();
void detruire_client();

#endif
