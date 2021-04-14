#ifndef _LIBPROTOCOLE_H_
#define _LIBPROTOCOLE_H_

/*
    ****************************************
    *									   *
    * Fichier lib_protocole.h			   *
    * Commun à tous les projets SE2A4 2021 *
    *									   *
    ****************************************
*/

#include "libaffiche.h"

/*** Définition des constantes ***/

/* Définition des ports de communication */
#define PORT_CHAT_TCP "9999"
#define PORT_DIFFUSION_UDP "9998"
#define PORT_TOUCHES_UDP "9997"
#define PORT_GRAPHIQUE_UDP "9996"

/* Définition des commandes TCP */
#define CMD_IDENTIFIANT "\\"
#define CMD_CONNECTION "pseudo"
#define CMD_ENDGAME "endgame"
#define CMD_CRASH "c_cho"
#define CMD_IDCLIENT "iencli"

/* Définition des touches UDP */
#define BIT_TOUCHE_HAUT 0x01
#define BIT_TOUCHE_BAS 0x02
#define BIT_TOUCHE_GAUCHE 0x04
#define BIT_TOUCHE_DROITE 0x08
#define BIT_TOUCHE_TIRER 0x10

/*** Définition des structures de communication UDP ***/

/* Paquet d'identité du serveur */
typedef struct UDP_Diffusion {
    unsigned short id_serveur;
    unsigned short port_tcp;
    unsigned short port_udp_touches;
} pr_udp_identite_t;

/* Paquet d'envoi des touches */
typedef struct UDP_Touches {
    unsigned char id_client;
    unsigned char touches;
} pr_udp_touches_t;

/* Paquet d'envoi des objets graphiques */
typedef struct UDP_graph {
    unsigned short nb_objets;
    objet2D* objets;
} pr_udp_graph_t;

#endif
