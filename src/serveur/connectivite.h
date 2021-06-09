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

#define MUTEX_LIST 0
#define MUTEX_QUIT 1
#define MUTEX_PLAY 2

#define LABY_X 8
#define LABY_Y 8

#define ATTENTE_DIFFUSION 3
#define ATTENTE_GRAPHIQUE 50000
#define ATTENTE_RAFRAICHISSEMENT 7000

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
void thread_actualisation_jeu();
void thread_touches(int* ecoute);
void thread_graphique();

/**** Chat TCP ****/

void connexion_client(int dialogue, char* ip);
void deconnexion_client(int dialogue);
void reception_message(char* message, int taille);
void envoi_trame_chat(int dialogue, int id, int commande);
void diffuser_message_chat(pr_tcp_chat_t* trame);

/**** Diffusion UDP ****/

void diffuser_identite();

/**** Actualisation jeu ****/

void boucle_actualisation_jeu();

/**** Touches UDP ****/

void reception_touche(char* message, int taille, char* ip);

/**** Graphique UDP ****/

void calcul_graphique();

/** Fonctions externes **/

extern void demarrer_partie();
extern void arreter_partie();

#endif
