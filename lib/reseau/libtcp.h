/**** Bibliotheque liaison TCP  ****/

#ifndef _LIBTCP_H_
#define _LIBTCP_H_

/** Fichiers d'inclusion des bibliotheques **/

#include <netdb.h>
#include <netinet/tcp.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/types.h>

#include "libclientlist.h"
#include "libthread.h"

/** Constantes **/

#define MAX_TAMPON 2048

/** Variables **/

client_list_t* client_list;

/** Prototypes **/

int init_serveur_tcp(char* service, int connexions);
int boucle_serveur_tcp(int ecoute, void* (*traitement)(void*));
int init_client_tcp(char* hote, char* service);
void detruire_lien_tcp(int s);
void* tache_chat_tcp(void* arg);

#endif
