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

int init_serveur(char *service, int connexions);

int boucleServeur(int ecoute, void *(*traitement)(void *));

int connexionServeur(char *hote, char *service);

#endif
