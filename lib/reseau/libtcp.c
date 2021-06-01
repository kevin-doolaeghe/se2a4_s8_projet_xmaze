/** Fichiers d'inclusions **/

#include "libtcp.h"

/** Variables **/

int nbclients;

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
        perror("init_serveur_tcp.getaddrinfo");
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
        perror("init_serveur_tcp.socket");
        exit(EXIT_FAILURE);
    }

    /* Options utiles */
    int vrai = 1;
    if (setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &vrai, sizeof(vrai)) < 0) {
        perror("init_serveur_tcp.setsockopt (REUSEADDR)");
        exit(EXIT_FAILURE);
    }
    if (setsockopt(s, IPPROTO_TCP, TCP_NODELAY, &vrai, sizeof(vrai)) < 0) {
        perror("init_serveur_tcp.setsockopt (NODELAY)");
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

int boucle_serveur_tcp(int ecoute, void* (*traitement)(int, char*))
{
    int dialogue;
    int ret;

    while (1) {
        /* Attente d'une connexion */
        if ((dialogue = accept(ecoute, NULL, NULL)) < 0) {
            perror("boucle_serveur_tcp.accept");
            exit(EXIT_FAILURE);
        }

        if (nbclients < MAX_CONNEXION) {
            nbclients++;

            /* Recuperation des informations du client */
            socklen_t len;
            struct sockaddr_storage addr;
            char ipstr[INET6_ADDRSTRLEN];

            len = sizeof addr;
            ret = getpeername(dialogue, (struct sockaddr*)&addr, &len);
            if (ret < 0) {
                close(dialogue);

                perror("boucle_serveur_tcp.getpeername");
                exit(EXIT_FAILURE);
            }

            if (addr.ss_family == AF_INET) {
                struct sockaddr_in* s = (struct sockaddr_in*)&addr;
                inet_ntop(AF_INET, &s->sin_addr, ipstr, sizeof ipstr);
            } else { // AF_INET6
                struct sockaddr_in6* s = (struct sockaddr_in6*)&addr;
                inet_ntop(AF_INET6, &s->sin6_addr, ipstr, sizeof ipstr);
            }

#ifdef DEBUG
            printf("Peer IP address: %s\n", ipstr);
#endif

            /* Traitement pour la socket de dialogue */
            traitement(dialogue, ipstr);
        } else {
            char* msg = "Too much players are connected.";
            envoi_message_tcp(dialogue, msg, strlen(msg));
            close(dialogue);
        }
    }
}

int boucle_reception_tcp(int ecoute, void* (*traitement)(char*, int))
{
    char message[MAX_TAMPON_TCP];
    int nboctets;

    while (1) {
        /* Attente d'un message */
        nboctets = read(ecoute, message, MAX_TAMPON_TCP - 1);
        if (nboctets <= 0) {
            close(ecoute);
            nbclients--;
            return 0;
        }
        message[nboctets] = 0;

        /* Traitement de la trame recue */
        traitement(message, nboctets);
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
        perror("init_client_tcp.getaddrinfo");
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
        perror("init_client_tcp.socket");
        exit(EXIT_FAILURE);
    }

    /* Connection de la socket a l'hote */
    if (connect(s, resultat->ai_addr, resultat->ai_addrlen) < 0)
        return -1;

    /* Liberation de la structure d'informations */
    freeaddrinfo(origine);

    return s;
}

void detruire_lien_tcp(int s) { close(s); }

int lire_message_tcp(int s, char* message, int taille)
{
    return read(s, message, taille - 1);
}

int envoi_message_tcp(int s, char* message, int taille)
{
    return write(s, message, taille);
}
