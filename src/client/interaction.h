/**** Interaction du client ****/

#ifndef _INTERACTION_H_
#define _INTERACTION_H_

/** Fichiers d'inclusion des bibliotheques **/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "libserveur.h"
#include "libserveurlist.h"
#include "libstrlist.h"
#include "libtcp.h"

/** Constantes **/

#define CMD_HELP "help"
#define CMD_LIST "list"
#define CMD_CONN "connect"
#define CMD_MESG "send"

#define ID_HELP 1
#define ID_LIST 2
#define ID_CONN 3
#define ID_MESG 4
#define ID_OTHR -1

/** Variables globales **/

extern server_list_t serveur_list;
extern server_t serveur;

extern bool quitter_client;
extern bool partie_en_cours;

/** Prototypes **/

void boucle_saisie_commande();
void traitement_commande(int commande);
void lire_ligne();
void afficher_aide();
void afficher_erreur();
void envoyer_message();

extern void connexion_chat(int id);

#endif
