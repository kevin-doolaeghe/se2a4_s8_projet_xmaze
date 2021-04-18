/** Fichiers d'inclusions **/

#include "libserveurlist.h"

/** Fonctions **/

pt_server_cell_t allocate_server(server_t* server)
{
    pt_server_cell_t ptr = malloc(sizeof(server_cell_t));

    init_server(&(ptr->server));
    copy_server(&(ptr->server), server);
    ptr->next = NULL;

    return ptr;
}

void append_server_to_list(server_list_t* list, server_t* server)
{
    pt_server_cell_t ptr = allocate_server(server);
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

void add_server_to_list(server_list_t* list, server_t* server)
{
    if (!search_server_in_list(list, server)) {
        append_server_to_list(list, server);
    }
}

void delete_last_server_from_list(server_list_t* list)
{
    pt_server_cell_t ptr = *list;
    *list = ptr->next;

    destroy_server(&(ptr->server));
    free(ptr);
}

void delete_server_from_list(server_list_t* list, int id)
{
    pt_server_cell_t ptr = *list;
    pt_server_cell_t previous = NULL;

    while (ptr != NULL) {
        if (ptr->server.id == id) {
            if (previous == NULL) {
                delete_last_server_from_list(list);
            } else {
                previous->next = ptr->next;
                destroy_server(&(ptr->server));
                free(ptr);
            }
            break;
        }
        previous = ptr;
        ptr = ptr->next;
    }
}

void destroy_server_list(server_list_t* list)
{
    while (*list != NULL) {
        delete_last_server_from_list(list);
    }
}

int size_of_server_list(server_list_t* list)
{
    pt_server_cell_t ptr = *list;
    int size = 0;

    while (ptr != NULL) {
        size++;
        ptr = ptr->next;
    }

    return size;
}

server_t* get_client_by_id(server_list_t* list, int id)
{
    pt_server_cell_t ptr = *list;
    int cnt = 0;

    while (ptr != NULL) {
        if (cnt == id)
            return &(ptr->server);
        cnt++;
        ptr = ptr->next;
    }

    return NULL;
}

bool search_server_in_list(server_list_t* list, server_t* server)
{
    pt_server_cell_t ptr = *list;
    bool found = false;

    while (ptr != NULL) {
        if (ptr->server.id == server->id) {
            found = true;
            break;
        }

        ptr = ptr->next;
    }
    return found;
}

void copy_server_list(server_list_t* src, server_list_t* dst)
{
    pt_server_cell_t ptr = *src;

    while (ptr != NULL) {
        for (int i = 0; i < size_of_server_list(src); i++) {
            append_server_to_list(dst, &(ptr->server));
        }
        ptr = ptr->next;
    }
}

void print_server_list(server_list_t* list)
{
    pt_server_cell_t ptr = *list;

    while (ptr != NULL) {
        print_server(&(ptr->server));
        printf("-----------------\n");
        ptr = ptr->next;
    }
}
