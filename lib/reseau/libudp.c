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
        perror("initialisationSocketUDP.getaddrinfo");
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
        perror("initialisationSocketUDP.socket");
        exit(EXIT_FAILURE);
    }

    /* Options utiles */
    int vrai = 1;
    if (setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &vrai, sizeof(vrai)) < 0) {
        perror("initialisationServeurUDPgenerique.setsockopt (REUSEADDR)");
        exit(EXIT_FAILURE);
    }

    /* Specification de l'adresse de la socket */
    statut = bind(s, resultat->ai_addr, resultat->ai_addrlen);
    if (statut < 0) {
        perror("initialisationServeurUDP.bind");
        exit(EXIT_FAILURE);
    }

    /* Liberation de la structure d'informations */
    freeaddrinfo(origine);

    return s;
}

int boucle_serveur_udp(int s, void* (*traitement)(void*, void*, void*))
{
    while (1) {
        struct sockaddr_storage adresse;
        socklen_t taille = sizeof(adresse);
        unsigned char message[MAX_TAMPON_UDP];

        int nboctets = recvfrom(s, message, MAX_TAMPON_UDP - 1, 0, (struct sockaddr*)&adresse, &taille);
        if (nboctets < 0)
            return -1;

        message[nboctets] = '\0';

        char ip[INET6_ADDRSTRLEN];
        struct sockaddr* sa = (struct sockaddr*)&adresse;
        if (sa->sa_family == AF_INET) {
            inet_ntop(adresse.ss_family, &(((struct sockaddr_in*)sa)->sin_addr), ip, sizeof ip);
        } else {
            inet_ntop(adresse.ss_family, &(((struct sockaddr_in6*)sa)->sin6_addr), ip, sizeof ip);
        }

        // printf("listener: got packet from %s\n", ip);
        // printf("listener: packet is %d bytes long\n", nboctets);
        // printf("listener: packet contains \"%s\"\n", message);

        traitement(message, &nboctets, ip);
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
        perror("messageUDPgenerique.getaddrinfo");
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
        perror("messageUDPgenerique.socket");
        exit(EXIT_FAILURE);
    }

    /* Option sur la socket */
    int vrai = 1;
    if (setsockopt(s, SOL_SOCKET, SO_BROADCAST, &vrai, sizeof(vrai)) < 0) {
        perror("initialisationServeurUDPgenerique.setsockopt (BROADCAST)");
        exit(EXIT_FAILURE);
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

/*
void envoi_broadcast_udp(char* reseau, char* masque, char* service, char* message, int taille)
{
    struct sockaddr_in sa_reseau, sa_masque, sa_hote;
    char hote[INET_ADDRSTRLEN];

    inet_pton(AF_INET, reseau, &(sa_reseau.sin_addr));
    sa_reseau.sin_addr.s_addr = htonl(sa_reseau.sin_addr.s_addr);

    inet_pton(AF_INET, masque, &(sa_masque.sin_addr));
    sa_masque.sin_addr.s_addr = htonl(sa_masque.sin_addr.s_addr);

    sa_reseau.sin_addr.s_addr &= sa_masque.sin_addr.s_addr;
    int32_t nb_hotes = ~sa_masque.sin_addr.s_addr;

    // printf("reseau: %x\n", sa_reseau.sin_addr.s_addr);
    // printf("masque: %x\n", sa_masque.sin_addr.s_addr);
    // printf("nb_hotes: %u\n", nb_hotes);

    sa_hote = sa_reseau;

    int i;
    for (i = 0; i < nb_hotes; i++) {
        sa_hote.sin_addr.s_addr++;
        sa_hote.sin_addr.s_addr = ntohl(sa_hote.sin_addr.s_addr);

        inet_ntop(AF_INET, &(sa_hote.sin_addr), hote, INET_ADDRSTRLEN);
        sa_hote.sin_addr.s_addr = htonl(sa_hote.sin_addr.s_addr);

        // printf("hote n°%d: %s\n", i, hote);
        envoi_message_udp(hote, service, message, taille);
    }
}
*/