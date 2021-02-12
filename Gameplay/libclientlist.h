/**** Bibliotheque table des clients  ****/

#ifndef _LIBCLIENTLIST_H_
#define _LIBCLIENTLIST_H_

/** Fichiers d'inclusion des bibliotheques **/

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <stdbool.h>

#include "libclient.h"

/** Constantes **/

/** Variables **/

typedef struct client_cell_s client_cell_t;
struct client cell_s {
    client_t client;
    client_cell_t * next;
};

typedef client_cell_t * client_list_t;
typedef client_cell_t * pt_client_cell_t;

/** Prototypes **/

/*
client_list_t *allocate_client(client_t *client);

void create_client_list(client_list_t *list);

void destroy_client_list(client_list_t *list);

void init_client_list(client_list_t *list);

void clear_client_list(client_list_t *list);

void append_client_to_list(client_list_t *list, client_t *client);

void delete_last_client(client_list_t *list);

int size_of_record_list(client_list_t *list);

bool search_client(client_list_t *list, client_t client);

void copy_client_list(client_list_t * src, client_list_t * dst);
*/

PtCellRec allocate_record(Record record);

void append_to_record_list(ListRec * list, Record record);

void delete_last_record(ListRec * list);

void delete_record_list(ListRec * list);

int size_of_record_list(ListRec list);

bool search_record(ListRec list, Record record);

void add_record_to_list(ListRec * list, Record record);

void display_record_list(ListRec list);

void copy_record_list(ListRec * src, ListRec * dst);


#endif
