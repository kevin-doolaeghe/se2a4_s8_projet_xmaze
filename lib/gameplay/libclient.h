/**** Bibliotheque des clients  ****/

#ifndef _LIBCLIENT_H_
#define _LIBCLIENT_H_

/** Fichiers d'inclusion des bibliothèques **/

#include "libpos.h"
#include "libstr.h"
#include "libstrlist.h"

/** Constantes **/

#define MAX_SIZE_PSEUDO 16

/** Variables **/

typedef struct client_s client_t;
struct client_s {
    int fd;
    str_t pseudo;
    pos_t position;
    str_list_t message_list;
};

/** Prototypes **/

void init_client(client_t* client);
void destroy_client(client_t* client);
void set_client(client_t* client, int fd, char* pseudo, pos_t* position);
void set_client_fd(client_t* client, int fd);
void set_client_pseudo(client_t* client, char* pseudo);
void set_client_position(client_t* client, pos_t* position);
void copy_client(client_t* dst, client_t* src);
void print_client(client_t* client);

#endif
