/**** Header shell ****/

#ifndef _SHELL_H_
#define _SHELL_H_

/** Fichiers d'inclusion des bibliothèques **/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "libprotocole.h"
#include "libserveur.h"
#include "libserveurlist.h"
#include "libstrlist.h"
#include "libtcp.h"

/** Variables **/

extern server_list_t serveur_list;
extern server_t serveur;

extern bool quitter_client;
extern bool partie_en_cours;

/** Prototypes **/

void boucle_commande();
extern void connexion_chat(int id);
extern void envoi_message_chat(char* message);

#endif
