/**** Connectivite du client ****/

#ifndef _CONNECTIVITE_H_
#define _CONNECTIVITE_H_

/** Fichiers d'inclusion des bibliotheques **/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "libaffiche.h"
#include "libprotocole.h"
#include "libserveur.h"
#include "libserveurlist.h"
#include "libtcp.h"
#include "libthread.h"
#include "libudp.h"

/** Variables globales **/

extern server_list_t serveur_list;
extern server_t serveur;

extern int id;

extern bool quitter_client;
extern bool partie_en_cours;

/** Prototypes **/

/**** Taches ****/

void thread_chat(int* ecoute);
void thread_diffusion(int* ecoute);
void thread_touches();
void thread_graphique(int* ecoute);

/**** Chat TCP ****/

void connexion_chat(int id);
void reception_message_chat(char* message, int taille);

/**** Diffusion UDP ****/

void reception_identite(char* message, int taille, char* ip);

/**** Touches UDP ****/

void envoi_touche(int touche);
void gestion_evenements();

/**** Graphique UDP ****/

void reception_graphique(char* message, int taille, char* ip);

/** Fonctions **/

extern void detruire_client();

#endif
