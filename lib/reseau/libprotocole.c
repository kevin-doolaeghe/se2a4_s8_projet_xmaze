/** Fichiers d'inclusion **/

#include "libprotocole.h"

/** Fonctions **/

void traduire_trame_identite(pr_udp_identite_t* trame, char* message, int taille)
{
    if (taille >= sizeof(pr_udp_identite_t)) {
        trame->id_serveur = ((pr_udp_identite_t*)message)->id_serveur;
        trame->port_tcp = ((pr_udp_identite_t*)message)->port_tcp;
        trame->port_udp_touches = ((pr_udp_identite_t*)message)->port_udp_touches;
    } else {
        trame->id_serveur = -1;
        trame->port_tcp = -1;
        trame->port_udp_touches = -1;
    }
}

void traduire_trame_touches(pr_udp_touches_t* trame, char* message, int taille)
{
    if (taille >= sizeof(pr_udp_touches_t)) {
        trame->id_client = ((pr_udp_touches_t*)message)->id_client;
        trame->touches = ((pr_udp_touches_t*)message)->touches;
    } else {
        trame->id_client = -1;
        trame->touches = -1;
    }
}

void traduire_trame_graphique(pr_udp_graph_t* trame, char* message, int taille)
{
    trame->nb_objets = 0;
    trame->objets = NULL;
    if (taille >= sizeof(pr_udp_graph_t)) {
        trame->nb_objets = 0;
        int i, nb = sizeof(trame->nb_objets) - 1;
        for (i = 0; i <= nb; i++)
            trame->nb_objets += message[nb - i] << (i * 8);
        if (taille >= (sizeof(trame->nb_objets) + trame->nb_objets * sizeof(objet_2d_t)))
            trame->objets = (objet_2d_t*)&(message[sizeof(trame->nb_objets)]);
    }
}