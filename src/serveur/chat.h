/**** Header chat TCP ****/

#ifndef _CHAT_H_
#define _CHAT_H_

/** Fichiers d'inclusion des bibliothèques **/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "libaffiche.h"
#include "libclientlist.h"
#include "libprotocole.h"
#include "libtcp.h"
#include "libthread.h"

/** Variables **/

extern client_list_t client_list;

extern bool quitter_serveur;
extern bool partie_en_cours;

/** Prototypes **/

void tache_gestion_chat(int* dialogue);
void gestion_client(int dialogue, char* ip);
void tache_discussion_client(int* dialogue);
void reception_message(char* message, int taille);

#endif
