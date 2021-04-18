/**** Connectivite du serveur ****/

#ifndef _CONNECTIVITE_H_
#define _CONNECTIVITE_H_

/** Fichiers d'inclusion des bibliotheques **/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "libaffiche.h"
#include "libclientlist.h"
#include "libprotocole.h"
#include "libtcp.h"
#include "libthread.h"
#include "libudp.h"

/** Constantes **/

#define LABY_X 8
#define LABY_Y 8

#define ATTENTE_DIFFUSION 3
#define ATTENTE_GRAPHIQUE 50000

#define ID_SERVEUR 34567


/** Variables globales **/

extern client_list_t client_list;

extern bool quitter_serveur;
extern bool partie_en_cours;

/** Prototypes **/

/**** Taches ****/

void thread_chat_connexion(int* dialogue);
void thread_chat_dialogue(int* dialogue);
void thread_diffusion();
void thread_touches(int* ecoute);
void thread_graphique();

/**** Chat TCP ****/

void gestion_client(int dialogue, char* ip);
void reception_message(char* message, int taille);

/**** Diffusion UDP ****/

void diffuser_identite();

/**** Touches UDP ****/

void reception_touche(char* message, int taille, char* ip);

/**** Graphique UDP ****/

void calcul_graphique();

#endif
