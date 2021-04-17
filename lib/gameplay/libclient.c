/** Fichiers d'inclusions **/

#include "libclient.h"

/** Fonctions **/

void init_client(client_t* client)
{
    client->id = -1;
    client->fd = -1;
    init_str(&(client->ip));
    init_str(&(client->pseudo));
    init_pos(&(client->position));
    init_str_list(&(client->message_list));
}

void destroy_client(client_t* client)
{
    destroy_str(&(client->ip));
    destroy_str(&(client->pseudo));
    destroy_str_list(&(client->message_list));
}

void set_client(client_t* client, int id, int fd, char* ip, char* pseudo, pos_t* position)
{
    set_client_id(client, id);
    set_client_fd(client, fd);
    set_client_ip(client, ip);
    set_client_pseudo(client, pseudo);
    set_client_position(client, position);
}

void set_client_id(client_t* client, int id)
{
    client->id = id;
}

void set_client_fd(client_t* client, int fd)
{
    client->fd = fd;
}

void set_client_ip(client_t* client, char* ip)
{
    set_str_from_cstr(&(client->ip), ip);
}

void set_client_pseudo(client_t* client, char* pseudo)
{
    set_str_from_cstr(&(client->pseudo), pseudo);
}

void set_client_position(client_t* client, pos_t* position)
{
    copy_pos(&(client->position), position);
}

void copy_client(client_t* dst, client_t* src)
{
    dst->id = src->id;
    dst->fd = src->fd;
    set_str_from_str(&(dst->ip), &(src->ip));
    set_str_from_str(&(dst->pseudo), &(src->pseudo));
    dst->position = src->position;
    copy_str_list(&(dst->message_list), &(src->message_list));
}

void print_client(client_t* client)
{
    printf("id: %d\n", client->id);

    printf("fd: %d\n", client->fd);

    printf("ip: ");
    print_str(&(client->ip));
    printf("\n");

    printf("pseudo: ");
    print_str(&(client->pseudo));
    printf("\n");

    printf("position:\n");
    print_pos(&(client->position));

    printf("messages:\n");
    print_str_list(&(client->message_list));
}
