/**** Bibliotheque de la table des clients  ****/

#ifndef _LIBCLIENTLIST_H_
#define _LIBCLIENTLIST_H_

/** Fichiers d'inclusion des bibliotheques **/

#include <stdbool.h>

#include "libclient.h"

/** Types **/

typedef struct client_cell_s client_cell_t;
struct client_cell_s {
    client_t client;
    client_cell_t* next;
};

typedef client_cell_t* client_list_t;
typedef client_cell_t* pt_client_cell_t;

/** Prototypes **/

pt_client_cell_t allocate_client(client_t* client);
void append_client_to_list(client_list_t* list, client_t* client);
void add_client_to_list(client_list_t* list, client_t* client);
void delete_last_client_from_list(client_list_t* list);
void delete_client_from_list(client_list_t* list, int fd);
void destroy_client_list(client_list_t* list);
client_t* get_client_by_id(client_list_t* list, int id);
client_t* get_client_by_fd(client_list_t* list, int fd);
bool search_client_in_list(client_list_t* list, int fd);
void order_list(client_list_t* list);
int size_of_client_list(client_list_t* list);
void copy_client_list(client_list_t* src, client_list_t* dst);
void print_client_list(client_list_t* list);

#endif
