/** Fichiers d'inclusions **/

#include "libudp.h"

/** Fonctions **/

int init_serveur_udp(char* service)
{
    struct addrinfo precisions, *resultat, *origine;
    int statut;
    int s;

    /* Construction de la structure adresse */
    memset(&precisions, 0, sizeof precisions);
    precisions.ai_family = AF_UNSPEC;
    precisions.ai_socktype = SOCK_DGRAM;
    precisions.ai_flags = AI_PASSIVE;

    statut = getaddrinfo(NULL, service, &precisions, &origine);
    if (statut < 0) {
        perror("init_serveur_udp.getaddrinfo");
        exit(EXIT_FAILURE);
    }

    struct addrinfo* p;
    for (p = origine, resultat = origine; p != NULL; p = p->ai_next) {
        if (p->ai_family == AF_INET6) {
            resultat = p;
            break;
        }
    }

    /* Creation d'une socket */
    s = socket(resultat->ai_family, resultat->ai_socktype, resultat->ai_protocol);
    if (s < 0) {
        perror("init_serveur_udp.socket");
        exit(EXIT_FAILURE);
    }

    /* Options utiles */
    int vrai = 1;
    if (setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &vrai, sizeof(vrai)) < 0) {
        perror("init_serveur_udp.setsockopt (REUSEADDR)");
        exit(EXIT_FAILURE);
    }

    /* Specification de l'adresse de la socket */
    statut = bind(s, resultat->ai_addr, resultat->ai_addrlen);
    if (statut < 0) {
        perror("init_serveur_udp.bind");
        exit(EXIT_FAILURE);
    }

    /* Liberation de la structure d'informations */
    freeaddrinfo(origine);

    return s;
}

int boucle_serveur_udp(int ecoute, void* (*traitement)(char*, int, char*))
{
    char message[MAX_TAMPON_UDP];
    int nboctets;

    struct sockaddr_storage adresse;
    socklen_t taille = sizeof(adresse);

    while (1) {
        /* Attente d'un message */
        nboctets = recvfrom(ecoute, message, MAX_TAMPON_UDP - 1, 0, (struct sockaddr*)&adresse, &taille);
        if (nboctets <= 0) {
            close(ecoute);
            return -1;
        }
        message[nboctets] = 0;

        /* Recuperation de l'adresse IP */
        char ip[INET6_ADDRSTRLEN];
        struct sockaddr* sa = (struct sockaddr*)&adresse;
        if (sa->sa_family == AF_INET) {
            inet_ntop(adresse.ss_family, &(((struct sockaddr_in*)sa)->sin_addr), ip, sizeof ip);
        } else {
            inet_ntop(adresse.ss_family, &(((struct sockaddr_in6*)sa)->sin6_addr), ip, sizeof ip);
        }

        /* Traitement du message */
        traitement(message, nboctets, ip);
    }
    return 0;
}

void envoi_message_udp(char* hote, char* service, char* message, int taille)
{
    struct addrinfo precisions, *resultat, *origine;
    int statut;
    int s;

    /* Creation de l'adresse de socket */
    memset(&precisions, 0, sizeof precisions);
    precisions.ai_family = AF_UNSPEC;
    precisions.ai_socktype = SOCK_DGRAM;

    statut = getaddrinfo(hote, service, &precisions, &origine);
    if (statut < 0) {
        perror("envoi_message_udp.getaddrinfo");
        exit(EXIT_FAILURE);
    }

    struct addrinfo* p;
    for (p = origine, resultat = origine; p != NULL; p = p->ai_next) {
        if (p->ai_family == AF_INET6) {
            resultat = p;
            break;
        }
    }

    /* Creation d'une socket */
    s = socket(resultat->ai_family, resultat->ai_socktype, resultat->ai_protocol);
    if (s < 0) {
        perror("envoi_message_udp.socket");
        exit(EXIT_FAILURE);
    }

    /* Option sur la socket */
    int vrai = 1;
    if (setsockopt(s, SOL_SOCKET, SO_BROADCAST, &vrai, sizeof(vrai)) < 0) {
        perror("envoi_message_udp.setsockopt (BROADCAST)");
        exit(EXIT_FAILURE);
    }

    /* Envoi du message */
    int nboctets = sendto(s, message, taille, 0, resultat->ai_addr, resultat->ai_addrlen);
    if (nboctets < 0) {
        perror("envoi_message_udp.sento");
        exit(EXIT_FAILURE);
    }

    /* Liberation de la structure d'informations */
    freeaddrinfo(origine);

    /* Fermeture de la socket d'envoi */
    close(s);
}