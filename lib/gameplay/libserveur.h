/**** Bibliotheque du serveur  ****/

#ifndef _LIBSERVEUR_H_
#define _LIBSERVEUR_H_

/** Fichiers d'inclusion des bibliothèques **/

#include "libstr.h"

/** Constantes **/

/** Variables **/

typedef struct server_s server_t;
struct server_s {
    int id;
    int fd;
    str_t ip;
    unsigned short port_tcp;
    unsigned short port_udp_touches;
};

/** Prototypes **/

void init_server(server_t* server);
void destroy_server(server_t* server);
void set_server(server_t* server, int id, int fd, char* ip, unsigned short port_tcp, unsigned short port_udp_touches);
void set_server_id(server_t* server, int id);
void set_server_fd(server_t* server, int fd);
void set_server_ip(server_t* server, char* ip);
void set_server_port_tcp(server_t* server, unsigned short port_tcp);
void set_server_port_udp_touches(server_t* server, unsigned short port_udp_touches);
void copy_server(server_t* dst, server_t* src);
void print_server(server_t* server);

#endif
