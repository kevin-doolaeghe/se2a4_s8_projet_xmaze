/**** Interaction du client ****/

#ifndef _INTERACTION_H_
#define _INTERACTION_H_

/** Fichiers d'inclusion des bibliotheques **/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "libprotocole.h"
#include "libserveur.h"
#include "libserveurlist.h"
#include "libstrlist.h"
#include "libtcp.h"

/** Constantes **/

#define CMD_TAG '/'
#define CMD_EMPT_STR ""
#define CMD_IDTF_STR "/id"
#define CMD_NICK_STR "/nick"
#define CMD_STRT_STR "/start"
#define CMD_STOP_STR "/stop"
#define CMD_DISC_STR "/disconnect"
#define CMD_CONN_STR "/connect"
#define CMD_HELP_STR "/help"
#define CMD_LIST_STR "/list"

#define CMD_EMPT_ID 0
#define CMD_CONN_ID 7
#define CMD_HELP_ID 8
#define CMD_LIST_ID 9
#define CMD_OTHR_ID -1

/** Variables globales **/

extern server_list_t liste_serveur;
extern server_t serveur;

extern int id;

extern bool quitter_client;
extern bool connecte_au_serveur;
extern bool partie_en_cours;

/** Prototypes **/

void boucle_saisie_commande();
void traitement_commande(int commande, str_list_t* tokens);
void lire_ligne();
void afficher_aide();
void afficher_erreur_saisie();
void afficher_erreur_admin();
void afficher_erreur_serveur_inexistant();
void afficher_erreur_deja_connecte();
void afficher_erreur_non_connecte();
void afficher_erreur_partie_demarree();
void afficher_erreur_partie_arretee();
void envoi_message(int commande, str_list_t* tokens);

/** Fonctions externes **/

extern void connexion_serveur(int id);
extern void deconnexion_serveur();
extern void envoi_trame_chat(int dialogue, int id, int commande);

#endif
