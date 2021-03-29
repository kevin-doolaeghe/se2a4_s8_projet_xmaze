/** Fichiers d'inclusions **/

#include "libserveur.h"

/** Fonctions **/

void init_server(server_t* server)
{
    server->fd = -1;
    server->id = -1;

    init_str(&(server->ip));
    server->port_tcp = -1;
    server->port_udp_touches = -1;
}

void destroy_server(server_t* server)
{
    destroy_str(&(server->ip));
}

void set_server(server_t* server, int fd, unsigned short id, char* ip, unsigned short port_tcp, unsigned short port_udp_touches)
{
    server->fd = fd;
    server->id = id;

    set_str_from_cstr(&(server->ip), ip);
    server->port_tcp = port_tcp;
    server->port_udp_touches = port_udp_touches;
}

void copy_server(server_t* dst, server_t* src)
{
    dst->fd = src->fd;
    dst->id = src->id;

    set_str_from_str(&(dst->ip), &(src->ip));
    dst->port_tcp = src->port_tcp;
    dst->port_udp_touches = src->port_udp_touches;
}

void print_server(server_t* server)
{
    printf("fd: %d\n", server->fd);
    printf("id: %u\n", server->id);

    printf("ip: ");
    print_str(&(server->ip));
    printf("\n");

    printf("port_tcp: %u\n", server->port_tcp);
    printf("port_udp_touches: %u\n", server->port_udp_touches);
}
