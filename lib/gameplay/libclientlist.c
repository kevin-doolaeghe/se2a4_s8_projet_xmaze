/** Fichiers d'inclusions **/

#include "libclientlist.h"

/** Fonctions **/

pt_client_cell_t allocate_client(client_t* client)
{
    pt_client_cell_t ptr = malloc(sizeof(client_cell_t));

    init_client(&(ptr->client));
    copy_client(&(ptr->client), client);
    ptr->next = NULL;

    return ptr;
}

void append_client_to_list(client_list_t* list, client_t* client)
{
    pt_client_cell_t ptr = allocate_client(client);
    if (ptr == NULL) {
        return;
    }

    if (*list == NULL) {
        *list = ptr;
    } else {
        ptr->next = *list;
        *list = ptr;
    }
}

void add_client_to_list(client_list_t* list, client_t* client)
{
    if (!search_client_in_list(list, client->id)) {
        append_client_to_list(list, client);
    }
}

void delete_last_client_from_list(client_list_t* list)
{
    pt_client_cell_t ptr = *list;
    *list = ptr->next;

    destroy_client(&(ptr->client));
    free(ptr);
}

void delete_client_from_list(client_list_t* list, int id)
{
    pt_client_cell_t ptr = *list;
    pt_client_cell_t previous = NULL;

    while (ptr != NULL) {
        if (ptr->client.id == id) {
            if (previous == NULL) {
                delete_last_client_from_list(list);
            } else {
                previous->next = ptr->next;
                destroy_client(&(ptr->client));
                free(ptr);
            }
            break;
        }
        previous = ptr;
        ptr = ptr->next;
    }
}

void destroy_client_list(client_list_t* list)
{
    while (*list != NULL) {
        delete_last_client_from_list(list);
    }
}

client_t* get_client_by_id(client_list_t* list, int id)
{
    pt_client_cell_t ptr = *list;

    while (ptr != NULL) {
        if (ptr->client.id == id)
            return &(ptr->client);
        ptr = ptr->next;
    }

    return NULL;
}

bool search_client_in_list(client_list_t* list, int id)
{
    pt_client_cell_t ptr = *list;
    bool found = false;

    while (ptr != NULL) {
        if (ptr->client.id == id) {
            found = true;
            break;
        }

        ptr = ptr->next;
    }
    return found;
}

int size_of_client_list(client_list_t* list)
{
    pt_client_cell_t ptr = *list;
    int size = 0;

    while (ptr != NULL) {
        size++;
        ptr = ptr->next;
    }

    return size;
}

void copy_client_list(client_list_t* src, client_list_t* dst)
{
    pt_client_cell_t ptr = *src;

    while (ptr != NULL) {
        for (int i = 0; i < size_of_client_list(src); i++) {
            append_client_to_list(dst, &(ptr->client));
        }
        ptr = ptr->next;
    }
}

void print_client_list(client_list_t* list)
{
    pt_client_cell_t ptr = *list;

    while (ptr != NULL) {
        print_client(&(ptr->client));
        printf("-----------------\n");
        ptr = ptr->next;
    }
}
