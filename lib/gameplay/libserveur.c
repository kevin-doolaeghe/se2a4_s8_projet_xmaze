/** Fichiers d'inclusions **/

#include "libserveur.h"

/** Fonctions **/

void init_server(server_t* server)
{
    server->fd = -1;
    init_str(&(server->ip));
    server->port = -1;
}

void destroy_server(server_t* server)
{
    destroy_str(&(server->ip));
}

void set_server(server_t* server, int fd, char* ip, int port)
{
    server->fd = fd;
    set_str_from_cstr(&(server->ip), ip);
    server->port = port;
}

void copy_server(server_t* dst, server_t* src)
{
    dst->fd = src->fd;
    set_str_from_str(&(dst->ip), &(src->ip));
    dst->port = src->port;
}

void print_server(server_t* server)
{
    printf("fd: %d\n", server->fd);

    printf("ip: ");
    print_str(&(server->ip));
    printf("\n");

    printf("port: %d\n", server->port);
}
