/**** Bibliotheque liaison TCP  ****/

#ifndef _LIBTCP_H_
#define _LIBTCP_H_

/** Fichiers d'inclusion des bibliotheques **/

#include <netdb.h>
#include <netinet/tcp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

/** Constantes **/

#define MAX_TAMPON 2048
#define MAX_CONNEXION 16

/** Variables **/

int client_count;

/** Prototypes **/

int init_serveur_tcp(char* service);
int boucle_serveur_tcp(int ecoute, void* (*traitement)(void*));
int init_client_tcp(char* hote, char* service);
void detruire_lien_tcp(int s);
int lire_message_tcp(int s, char* message, int size);
void envoi_message_tcp(int s, char* message, int size);

#endif
