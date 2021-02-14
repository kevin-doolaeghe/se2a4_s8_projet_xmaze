/**** Bibliotheque liaison UDP  ****/

#ifndef _LIBUDP_H_
#define _LIBUDP_H_

/** Fichiers d'inclusion des bibliotheques **/

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netdb.h>

/** Constantes **/

#define MAX_UDP_MESSAGE 256

/** Variables **/


/** Prototypes **/

int init_serveur_udp(char *service);

int boucle_serveur_udp(int s, void *(*traitement)(void *, void *));

int init_client_udp(char *hote, char *service);

void detruire_lien_udp(int s);

void envoi_message_udp(int s, unsigned char *message, int taille);

#endif
