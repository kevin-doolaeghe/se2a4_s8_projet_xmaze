#include "libudp.h"

int init_serveur_udp(char *service) {
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
        perror("initialisationSocketUDP.getaddrinfo");
        exit(EXIT_FAILURE);
    }

    struct addrinfo *p;
    for (p = origine, resultat = origine; p != NULL; p = p->ai_next) {
        if (p->ai_family == AF_INET6) {
            resultat = p;
            break;
        }
    }

    /* Creation d'une socket */
    s = socket(resultat->ai_family, resultat->ai_socktype, resultat->ai_protocol);
    if (s < 0) {
        perror("initialisationSocketUDP.socket");
        exit(EXIT_FAILURE);
    }

    /* Options utiles */
    int vrai = 1;
    if (setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &vrai, sizeof(vrai)) < 0) {
        perror("initialisationServeurUDPgenerique.setsockopt (REUSEADDR)");
        exit(-1);
    }

    /* Specification de l'adresse de la socket */
    statut = bind(s, resultat->ai_addr, resultat->ai_addrlen);
    if (statut < 0) {
        perror("initialisationServeurUDP.bind");
        exit(-1);
    }

    /* Liberation de la structure d'informations */
    freeaddrinfo(origine);

    return s;
}

int boucle_serveur_udp(int s, void *(*traitement)(void *)) {
    while (1) {
        struct sockaddr_storage adresse;
        socklen_t taille = sizeof(adresse);
        unsigned char message[MAX_UDP_MESSAGE];

        int nboctets = recvfrom(s, message, MAX_UDP_MESSAGE, 0, (struct sockaddr *) &adresse, &taille);
        if (nboctets < 0) return -1;
        if (traitement(message, nboctets) < 0) break;
    }
    return 0;
}

void envoi_message_udp(char *hote, char *service, unsigned char *message, int taille) {
    struct addrinfo precisions, *resultat, *origine;
    int statut;
    int s;

    /* Creation de l'adresse de socket */
    memset(&precisions, 0, sizeof precisions);
    precisions.ai_family = AF_UNSPEC;
    precisions.ai_socktype = SOCK_DGRAM;
    
    statut = getaddrinfo(hote, service, &precisions, &origine);
    if (statut < 0) {
        perror("messageUDPgenerique.getaddrinfo");
        exit(EXIT_FAILURE);
    }

    struct addrinfo *p;
    for (p = origine, resultat = origine; p != NULL; p = p->ai_next) {
        if (p->ai_family == AF_INET6) {
            resultat = p;
            break;
        }
    }

    /* Creation d'une socket */
    s = socket(resultat->ai_family, resultat->ai_socktype, resultat->ai_protocol);
    if (s < 0) {
        perror("messageUDPgenerique.socket");
        exit(EXIT_FAILURE);
    }

    /* Option sur la socket */
    int vrai = 1;
    if (setsockopt(s, SOL_SOCKET, SO_BROADCAST, &vrai, sizeof(vrai)) < 0) {
        perror("initialisationServeurUDPgenerique.setsockopt (BROADCAST)");
        exit(-1);
    }

    /* Envoi du message */
    int nboctets = sendto(s, message, taille, 0, resultat->ai_addr, resultat->ai_addrlen);
    if (nboctets < 0) {
        perror("messageUDPgenerique.sento");
        exit(EXIT_FAILURE);
    }

    /* Liberation de la structure d'informations */
    freeaddrinfo(origine);

    /* Fermeture de la socket d'envoi */
    close(s);
}
