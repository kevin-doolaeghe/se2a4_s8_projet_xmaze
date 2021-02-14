/**** Bibliotheque liaison TCP  ****/

#ifndef _LIBTCP_H_
#define _LIBTCP_H_

/** Fichiers d'inclusion des bibliotheques **/

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>

/** Constantes **/


/** Variables **/


/** Prototypes **/

int init_serveur_tcp(char *service, int connexions);

int boucle_serveur_tcp(int ecoute, void *(*traitement)(void *));

int init_client_tcp(char *hote, char *service);

#endif
