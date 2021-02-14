/**** Bibliotheque liaison UDP  ****/

#ifndef _LIBUDP_H_
#define _LIBUDP_H_

/** Fichiers d'inclusion des bibliotheques **/

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>

/** Constantes **/


/** Variables **/


/** Prototypes **/

int init_serveur_udp(char *service);

int boucle_serveur_udp(int s, void *(*traitement)(void *));

int init_client_udp(char *hote, char *service);

void envoi_message_udp(int s, unsigned char *message, int taille);

#endif
