/**** Bibliotheque client ****/

/** Fichiers d'inclusions **/

#include "libclientlist.h"

/** Fonctions **/

pt_client_cell_t allocate_client(client_t client) {
    pt_client_cell_t ptr = malloc(sizeof(client_cell_t));

    ptr->client = client;
    ptr->next   = NULL;

    return ptr;
}

void append_client_to_list(client_list_t *list, client_t client) {
    pt_client_cell_t ptr = allocate_client(client);
    if (ptr == NULL) { return; }

    ptr->next = *list;
    *list     = ptr;
}

void delete_last_client(client_list_t *list) {
    pt_client_cell_t ptr = *list;
    *list                = ptr->next;

    free(ptr);
}

void destroy_client_list(client_list_t *list) {
    pt_client_cell_t ptr = *list;

    while (ptr != NULL) {
        delete_last_client(&ptr);
    }
}

int size_of_client_list(client_list_t *list) {
    pt_client_cell_t ptr = *list;
    int             size = 0;

    while (ptr != NULL) {
        size++;
        ptr = ptr->next;
    }

    return size;
}

bool search_client(client_list_t *list, client_t client) {
    pt_client_cell_t ptr = *list;

    /*
    while (ptr != NULL) {
        if (//TODO) { return true; }
        ptr = ptr->next;
    }
    */

    return false;
}

void copy_client_list(client_list_t *src, client_list_t *dst) {
    pt_client_cell_t ptr = *src;

    while (ptr != NULL) {
        for (int i = 0; i < size_of_client_list(src); i++) {
            append_client_to_list(dst, ptr->client);
        }
        ptr = ptr->next;
    }
}

void print_client_list(client_list_t list) {
    pt_client_cell_t ptr = list;

    while (ptr != NULL) {
        print_client(&(ptr->client));
        printf("-----------------\n");
        ptr = ptr->next;
    }
}
