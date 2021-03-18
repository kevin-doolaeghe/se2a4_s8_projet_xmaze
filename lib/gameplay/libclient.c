/**** Bibliotheque client ****/

/** Fichiers d'inclusions **/

#include "libclient.h"

/** Fonctions **/

void init_client(client_t* client)
{
    client->fd = -1;
    init_str(&(client->pseudo));
    init_pos(&(client->position));
}

void destroy_client(client_t* client)
{
    destroy_str(&(client->pseudo));
    free(client);
}

void print_client(client_t* client)
{
    printf("fd: %d\n", client->fd);

    printf("pseudo: ");
    print_str(&(client->pseudo));
    printf("\n");

    print_pos(&(client->position));
}

void set_client(client_t* client, int fd, char* pseudo, pos_t* position)
{
    client->fd = fd;
    set_str(&(client->pseudo), pseudo);
    set_pos(&(client->position), position);
}