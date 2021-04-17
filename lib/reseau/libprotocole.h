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

/** Fichiers d'inclusion des bibliotheques **/

#include <stdio.h>
#include <stdlib.h>

/** Constantes **/

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

/** Types **/

/* Paquet d'identité du serveur */

typedef struct pr_udp_identite_s pr_udp_identite_t;
struct pr_udp_identite_s {
    unsigned short id_serveur;
    unsigned short port_tcp;
    unsigned short port_udp_touches;
};

/* Paquet d'envoi des touches */

typedef struct pr_udp_touches_s pr_udp_touches_t;
struct pr_udp_touches_s {
    unsigned char id_client;
    unsigned char touches;
};

/* Structures graphiques */

typedef struct {
    int x, y;
} coords_t;

typedef struct {
    int type;
    union {
        coords_t p[4];
    } def;
} objet_2d_t;

/* Paquet d'envoi des objets graphiques */

typedef struct pr_udp_graph_s pr_udp_graph_t;
struct pr_udp_graph_s {
    int nb_objets;
    objet_2d_t* objets;
};

/** Prototypes **/

void traduire_trame_identite(pr_udp_identite_t* trame, char* message, int taille);
void traduire_trame_touches(pr_udp_touches_t* trame, char* message, int taille);
void traduire_trame_graphique(pr_udp_graph_t* trame, char* message, int taille);

#endif
