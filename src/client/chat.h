/**** Header chat TCP ****/

#ifndef _CHAT_H_
#define _CHAT_H_

/** Fichiers d'inclusion des bibliothèques **/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "graphiques.h"
#include "libprotocole.h"
#include "libserveur.h"
#include "libserveurlist.h"
#include "libtcp.h"
#include "libthread.h"

/** Variables **/

extern server_list_t serveur_list;
extern server_t serveur;

extern int id;

extern bool quitter_client;
extern bool partie_en_cours;

/** Prototypes **/

void connexion_chat(int id);
void tache_ecoute_chat(int* ecoute);
void reception_message_chat(char* message, int taille);
void envoi_message_chat(char* message);

#endif
