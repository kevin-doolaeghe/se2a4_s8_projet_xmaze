/**** Entete du serveur ****/

#ifndef _SERVEUR_H_
#define _SERVEUR_H_

/** Fichiers d'inclusion des bibliotheques **/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "libclientlist.h"
#include "libsig.h"
#include "libthread.h"

#include "connectivite.h"

/** Variables globales **/

client_list_t client_list;

bool quitter_serveur;
bool partie_en_cours;

/** Prototypes **/

int main(int argc, char* argv[]);
void usage();
void init_serveur();
void detruire_serveur();
void connexion_client(int dialogue, char* ip);
void deconnexion_client(int dialogue);
void demarrer_partie();
void arreter_partie();

#endif
