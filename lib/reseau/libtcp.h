/**** Bibliotheque liaison TCP  ****/

#ifndef _LIBTCP_H_
#define _LIBTCP_H_

/** Fichiers d'inclusion des bibliotheques **/

#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/tcp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/** Constantes **/

#define MAX_TAMPON_TCP 2048
#define MAX_CONNEXION 16

/** Prototypes **/

int init_serveur_tcp(char* service);
int boucle_serveur_tcp(int ecoute, void* (*traitement)(int, char*));
int boucle_reception_tcp(int ecoute, void* (*traitement)(char*, int));
int init_client_tcp(char* hote, char* service);
void detruire_lien_tcp(int s);
int lire_message_tcp(int s, char* message, int taille);
int envoi_message_tcp(int s, char* message, int taille);

#endif
