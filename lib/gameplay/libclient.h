/**** Bibliotheque des clients  ****/

#ifndef _LIBCLIENT_H_
#define _LIBCLIENT_H_

/** Fichiers d'inclusion des bibliotheques **/

#include "libmissile.h"
#include "libpos.h"
#include "libstr.h"
#include "libstrlist.h"

/** Types **/

typedef struct client_s client_t;
struct client_s {
    int id;
    int fd;
    str_t ip;
    str_t pseudo;
    pos_t position;
    str_list_t message_list;
    missile_t missile;
};

/** Prototypes **/

void init_client(client_t* client);
void destroy_client(client_t* client);
void set_client(client_t* client, int id, int fd, char* ip, char* pseudo, pos_t* position);
void set_client_id(client_t* client, int id);
void set_client_fd(client_t* client, int fd);
void set_client_ip(client_t* client, char* ip);
void set_client_pseudo(client_t* client, char* pseudo);
void set_client_position(client_t* client, pos_t* position);
void set_client_missile(client_t* client, missile_t* missile);
void set_client_missile_position(client_t* client, pos_t* position);
void activer_tir(client_t* client);
void desactiver_tir(client_t* client);
void copy_client(client_t* dst, client_t* src);
void print_client(client_t* client);

#endif
