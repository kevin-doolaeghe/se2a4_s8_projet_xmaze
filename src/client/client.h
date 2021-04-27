/**** Entete du client ****/

#ifndef _CLIENT_H_
#define _CLIENT_H_

/** Fichiers d'inclusion des bibliotheques **/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "libserveur.h"
#include "libserveurlist.h"
#include "libsig.h"
#include "libthread.h"

#include "connectivite.h"
#include "interaction.h"

/** Variables globales **/

server_list_t liste_serveur;
server_t serveur;

int id;

bool quitter_client;
bool connecte_au_serveur;
bool partie_en_cours;

/** Prototypes **/

int main(int argc, char* argv[]);
void usage();
void init_client();
void detruire_client();
void connexion_serveur(int id);
void deconnexion_serveur();
void demarrer_jeu();
void arreter_jeu();

#endif
