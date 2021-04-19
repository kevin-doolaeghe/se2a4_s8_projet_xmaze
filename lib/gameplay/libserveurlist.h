/**** Bibliotheque de la table des clients  ****/

#ifndef _LIBSERVEURLIST_H_
#define _LIBSERVEURLIST_H_

/** Fichiers d'inclusion des bibliotheques **/

#include <stdbool.h>

#include "libserveur.h"

/** Types **/

typedef struct server_cell_s server_cell_t;
struct server_cell_s {
    server_t server;
    server_cell_t* next;
};

typedef server_cell_t* server_list_t;
typedef server_cell_t* pt_server_cell_t;

/** Prototypes **/

pt_server_cell_t allocate_server(server_t* server);
void append_server_to_list(server_list_t* list, server_t* server);
void add_server_to_list(server_list_t* list, server_t* server);
void delete_last_server_from_list(server_list_t* list);
void delete_server_from_list(server_list_t* list, int id);
void destroy_server_list(server_list_t* list);
int size_of_server_list(server_list_t* list);
server_t* get_server_by_id(server_list_t* list, int id);
bool search_server_in_list(server_list_t* list, int id);
void copy_server_list(server_list_t* src, server_list_t* dst);
void print_server_list(server_list_t* list);

#endif
