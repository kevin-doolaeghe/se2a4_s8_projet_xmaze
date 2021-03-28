/**** Bibliotheque du serveur  ****/

#ifndef _LIBSERVEUR_H_
#define _LIBSERVEUR_H_

/** Fichiers d'inclusion des bibliothèques **/

#include "libstr.h"

/** Constantes **/

/** Variables **/

typedef struct server_s server_t;
struct server_s {
    int fd;
    str_t ip;
    int port;
};

/** Prototypes **/

void init_server(server_t* server);
void destroy_server(server_t* server);
void set_server(server_t* server, int fd, char* ip, int port);
void copy_server(server_t* dst, server_t* src);
void print_server(server_t* server);

#endif
