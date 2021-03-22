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
    client_list = NULL;
    client_count = 0;

    int dialogue;

    client_t client;
    init_client(&client);

    while (1) {
        /* Attente d'une connexion */
        if ((dialogue = accept(ecoute, NULL, NULL)) < 0)
            return -1;

        if (client_count < MAX_CONNEXION) {
            client_count++;
            client.fd = dialogue;

            append_client_to_list(&client_list, &client);

            /* Creation d'un thread avec le socket de dialogue */
            creer_tache((void* (*)(void*))traitement, (void*)&dialogue, sizeof(dialogue));
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
    return read(s, message, size);
}

void envoi_message_tcp(int s, char* message, int size)
{
    write(s, message, size);
}

void tache_chat_tcp(void* arg)
{
    int dialogue = *(int*)arg;
    char tampon[MAX_TAMPON];
    int ret;

    while ((ret = lire_message_tcp(dialogue, tampon, MAX_TAMPON - 1)) > 0) {
        if (ret <= 0) {
            detruire_lien_tcp(dialogue);
            client_count--;
            return;
        }
        tampon[ret] = 0;
        printf("tampon: %s\n", tampon);
        print_client_list(&client_list);
    }
}