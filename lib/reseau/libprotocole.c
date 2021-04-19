/** Fichiers d'inclusion **/

#include "libprotocole.h"

/** Fonctions **/

void traduire_trame_chat(pr_tcp_chat_t* dst, char* src, int taille)
{
    dst->id_client = -1;
    dst->commande = -1;
    dst->message = NULL;

    if (taille >= sizeof(dst->id_client) + sizeof(dst->commande)) {
        dst->id_client = ((pr_tcp_chat_t*)src)->id_client;
        dst->commande = ((pr_tcp_chat_t*)src)->commande;
        if (taille > sizeof(dst->id_client) + sizeof(dst->commande))
            dst->message = &src[sizeof(dst->id_client) + sizeof(dst->commande)];
    }
}

void traduire_trame_identite(pr_udp_identite_t* dst, char* src, int taille)
{
    if (taille >= sizeof(pr_udp_identite_t)) {
        dst->id_serveur = ((pr_udp_identite_t*)src)->id_serveur;
        dst->port_tcp = ((pr_udp_identite_t*)src)->port_tcp;
        dst->port_udp_touches = ((pr_udp_identite_t*)src)->port_udp_touches;
    } else {
        dst->id_serveur = -1;
        dst->port_tcp = -1;
        dst->port_udp_touches = -1;
    }
}

void traduire_trame_touches(pr_udp_touches_t* dst, char* src, int taille)
{
    if (taille >= sizeof(pr_udp_touches_t)) {
        dst->id_client = ((pr_udp_touches_t*)src)->id_client;
        dst->touches = ((pr_udp_touches_t*)src)->touches;
    } else {
        dst->id_client = -1;
        dst->touches = -1;
    }
}

void traduire_trame_graphique(pr_udp_graph_t* dst, char* src, int taille)
{
    dst->nb_objets = 0;
    dst->objets = NULL;
    if (taille >= sizeof(pr_udp_graph_t)) {
        dst->nb_objets = 0;
        int i, nb = sizeof(dst->nb_objets) - 1;
        for (i = 0; i <= nb; i++)
            dst->nb_objets += src[nb - i] << (i * 8);
        if (taille >= (sizeof(dst->nb_objets) + dst->nb_objets * sizeof(objet_2d_t)))
            dst->objets = (objet_2d_t*)&(src[sizeof(dst->nb_objets)]);
    }
}

void ecrire_trame_chat(pr_tcp_chat_t* src, char* dst, int taille)
{
    int index = sizeof(src->id_client) + sizeof(src->id_client);
    if (src->message == NULL) {
        if (taille >= index)
            memcpy(dst, src, sizeof(pr_tcp_chat_t));
    } else {
        if (taille >= index + strlen(src->message)) {
            memcpy(dst, src, sizeof(pr_tcp_chat_t));
            memcpy(dst + index, src->message, strlen(src->message));
        }
    }
}

void ecrire_trame_identite(pr_udp_identite_t* src, char* dst, int taille)
{
    if (taille >= sizeof(pr_udp_identite_t))
        memcpy(dst, src, sizeof(pr_udp_identite_t));
}

void ecrire_trame_touches(pr_udp_touches_t* src, char* dst, int taille)
{
    if (taille >= sizeof(pr_udp_touches_t))
        memcpy(dst, src, sizeof(pr_udp_touches_t));
}

void ecrire_trame_graphique(pr_udp_graph_t* src, char* dst, int taille)
{
    if (taille >= sizeof(src->nb_objets) + src->nb_objets * sizeof(objet_2d_t)) {
        int i;
        for (i = 0; i < sizeof(src->nb_objets); i++)
            dst[i] = (src->nb_objets >> (3 - i) * 8) & 0xFF;
        for (i = 0; i < src->nb_objets; i++)
            memcpy(dst + sizeof(src->nb_objets) + i * sizeof(objet_2d_t), &(src->objets[i]), sizeof(objet_2d_t));
    }
}