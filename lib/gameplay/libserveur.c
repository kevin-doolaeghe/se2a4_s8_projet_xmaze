/** Fichiers d'inclusions **/

#include "libserveur.h"

/** Fonctions **/

void init_server(server_t* server)
{
    server->fd = -1;

    init_str(&(server->ip));
    server->port_tcp = -1;
    server->port_udp_touches = -1;
}

void destroy_server(server_t* server)
{
    destroy_str(&(server->ip));
}

void set_server(server_t* server, int fd, char* ip, unsigned short port_tcp, unsigned short port_udp_touches)
{
    set_server_fd(server, fd);
    set_server_ip(server, ip);
    set_server_port_tcp(server, port_tcp);
    set_server_port_udp_touches(server, port_udp_touches);
}

void set_server_fd(server_t* server, int fd)
{
    server->fd = fd;
}

void set_server_ip(server_t* server, char* ip)
{
    set_str_from_cstr(&(server->ip), ip);
}

void set_server_port_tcp(server_t* server, unsigned short port_tcp)
{
    server->port_tcp = port_tcp;
}

void set_server_port_udp_touches(server_t* server, unsigned short port_udp_touches)
{
    server->port_udp_touches = port_udp_touches;
}

void copy_server(server_t* dst, server_t* src)
{
    dst->fd = src->fd;

    set_str_from_str(&(dst->ip), &(src->ip));
    dst->port_tcp = src->port_tcp;
    dst->port_udp_touches = src->port_udp_touches;
}

int decode_server_from_cstr(server_t* server, char* str)
{
    if (sizeof(str) >= sizeof(server_t)) {
        server = (server_t*)str;
        return 0;
    } else {
        return -1;
    }
}

void print_server(server_t* server)
{
    printf("fd: %d\n", server->fd);

    printf("ip: ");
    print_str(&(server->ip));
    printf("\n");

    printf("port_tcp: %u\n", server->port_tcp);
    printf("port_udp_touches: %u\n", server->port_udp_touches);
}
