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
#define KEY_UP 0
#define KEY_DOWN 1
#define KEY_LEFT 2
#define KEY_RIGHT 3
#define KEY_JUMP 4
#define KEY_SHOOT 5

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

/* Objet graphique */
/***** NON DEFINITIF *****/
typedef struct objet {
    //	unsigned short type;
    //	unsigned short pos_x;
    //	unsigned short pos_z;
} pr_objet_t;

/* Paquet d'envoi des objets graphiques */
/***** NON DEFINITIF *****/
typedef struct UDP_graph {
    //	unsigned short nb_objets;
    //	struct objet objets[nb_objets];
} pr_udp_graph_t;

#endif
