/** Fichiers d'inclusions **/

#include "libclient.h"

/** Fonctions **/

void init_client(client_t* client)
{
    client->fd = -1;
    init_str(&(client->pseudo));
    init_pos(&(client->position));
    init_str_list(&(client->message_list));
}

void destroy_client(client_t* client)
{
    destroy_str(&(client->pseudo));
    destroy_str_list(&(client->message_list));
    free(client);
}

void set_client(client_t* client, int fd, char* pseudo, pos_t* position)
{
    set_client_fd(client, fd);
    set_client_pseudo(client, pseudo);
    set_client_position(client, position);
}

void set_client_fd(client_t* client, int fd)
{
    client->fd = fd;
}

void set_client_pseudo(client_t* client, char* pseudo)
{
    set_str(&(client->pseudo), pseudo);
}

void set_client_position(client_t* client, pos_t* position)
{
    copy_pos(&(client->position), position);
}

void copy_client(client_t* dst, client_t* src)
{
    dst->fd = src->fd;
    copy_str(&(dst->pseudo), &(src->pseudo));
    dst->position = src->position;
    copy_str_list(&(dst->message_list), &(src->message_list));
}

void print_client(client_t* client)
{
    printf("fd: %d\n", client->fd);

    printf("pseudo: ");
    print_str(&(client->pseudo));
    printf("\n");

    printf("messages:\n");
    print_str_list(&(client->message_list));

    printf("position:\n");
    print_pos(&(client->position));
}
