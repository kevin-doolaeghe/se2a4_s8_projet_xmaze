/**** Bibliotheque liaison UDP  ****/

#ifndef _LIBUDP_H_
#define _LIBUDP_H_

/** Fichiers d'inclusion des bibliotheques **/

#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/types.h>

/** Constantes **/

#define MAX_UDP_MESSAGE 256

/** Variables **/

/** Prototypes **/

int init_serveur_udp(char* service);
int boucle_serveur_udp(int s, void* (*traitement)(void*, void*));
int init_client_udp(char* hote, char* service);
void detruire_lien_udp(int s);
void envoi_message_udp(int s, unsigned char* message, int taille);
void* tache_diffusion_udp(void* arg);
void* tache_touches_udp(void* arg);
void* tache_graphique_udp(void* arg);

#endif
