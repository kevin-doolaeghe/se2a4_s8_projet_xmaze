/**** Bibliotheque liaison UDP  ****/

#ifndef _LIBUDP_H_
#define _LIBUDP_H_

/** Fichiers d'inclusion des bibliotheques **/

#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

/** Constantes **/

#define MAX_UDP_MESSAGE 256

/** Variables **/

/** Prototypes **/

int init_serveur_udp(char* service);
int boucle_serveur_udp(int s, void* (*traitement)(void*, void*));
int init_client_udp(char* hote, char* service);
void envoi_message_udp(char* hote, char* service, char* message, int taille);

#endif
