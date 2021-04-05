/** Fichiers d'inclusions **/

#include "libtcp.h"

/** Fonctions **/

int init_serveur_tcp(char* service)
{
    struct addrinfo precisions, *resultat, *origine;
    int statut;
    int s;

    /* Construction de la structure adresse */
    memset(&precisions, 0, sizeof precisions);
    precisions.ai_family = AF_UNSPEC;
    precisions.ai_socktype = SOCK_STREAM;
    precisions.ai_flags = AI_PASSIVE;

    statut = getaddrinfo(NULL, service, &precisions, &origine);
    if (statut < 0) {
        perror("initialisationServeur.getaddrinfo");
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
        perror("initialisationServeur.socket");
        exit(EXIT_FAILURE);
    }

    /* Options utiles */
    int vrai = 1;
    if (setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &vrai, sizeof(vrai)) < 0) {
        perror("initialisationServeur.setsockopt (REUSEADDR)");
        exit(EXIT_FAILURE);
    }
    if (setsockopt(s, IPPROTO_TCP, TCP_NODELAY, &vrai, sizeof(vrai)) < 0) {
        perror("initialisationServeur.setsockopt (NODELAY)");
        exit(EXIT_FAILURE);
    }

    /* Specification de l'adresse de la socket */
    statut = bind(s, resultat->ai_addr, resultat->ai_addrlen);
    if (statut < 0)
        return -1;

    /* Liberation de la structure d'informations */
    freeaddrinfo(origine);

    /* Taille de la queue d'attente */
    statut = listen(s, MAX_CONNEXION);
    if (statut < 0)
        return -1;

    return s;
}

int boucle_serveur_tcp(int ecoute, void* (*traitement)(void*))
{
    int dialogue;
    while (1) {
        /* Attente d'une connexion */
        if ((dialogue = accept(ecoute, NULL, NULL)) < 0)
            return -1;

        if (client_count < MAX_CONNEXION) {
            client_count++;

            /* Creation d'un thread avec le socket de dialogue */
            traitement((void*)&dialogue);
        } else {
            detruire_lien_tcp(dialogue);
        }
    }
}

int init_client_tcp(char* hote, char* service)
{
    struct addrinfo precisions, *resultat, *origine;
    int statut;
    int s;

    /* Creation de l'adresse de socket */
    memset(&precisions, 0, sizeof precisions);
    precisions.ai_family = AF_UNSPEC;
    precisions.ai_socktype = SOCK_STREAM;

    statut = getaddrinfo(hote, service, &precisions, &origine);
    if (statut < 0) {
        perror("connexionServeur.getaddrinfo");
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
        perror("connexionServeur.socket");
        exit(EXIT_FAILURE);
    }

    /* Connection de la socket a l'hote */
    if (connect(s, resultat->ai_addr, resultat->ai_addrlen) < 0)
        return -1;

    /* Liberation de la structure d'informations */
    freeaddrinfo(origine);

    return s;
}

void detruire_lien_tcp(int s) { shutdown(s, SHUT_RDWR); }

int lire_message_tcp(int s, char* message, int size)
{
    /*
    struct sockaddr_in addr;
    socklen_t len;

    int ret = getpeername(s, (struct sockaddr*)&addr, &len);
    if (ret < 0) {
        perror("Error : Could not get socket info");
        close(s);
        exit(-1);
    }
    */
    return read(s, message, size);
}

int envoi_message_tcp(int s, char* message, int size)
{
    return write(s, message, size);
}