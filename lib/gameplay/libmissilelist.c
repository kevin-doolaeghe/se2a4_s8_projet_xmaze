/** Fichiers d'inclusions **/

#include "libmissilelist.h"

/** Fonctions **/

pt_missile_cell_t allocate_missile(missile_t* missile)
{
    pt_missile_cell_t ptr = malloc(sizeof(missile_cell_t));

    init_missile(&(ptr->missile));
    set_missile(&(ptr->missile), missile->id, &(missile->position), missile->tireur);
    ptr->next = NULL;

    return ptr;
}

void append_missile_to_list(missile_list_t* list, missile_t* missile)
{
    pt_missile_cell_t ptr = allocate_missile(missile);
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

void delete_last_missile_from_list(missile_list_t* list)
{
    pt_missile_cell_t ptr = *list;
    *list = ptr->next;

    free(ptr);
}

void delete_missile_from_list(missile_list_t* list, int id)
{
    pt_missile_cell_t ptr = *list;
    pt_missile_cell_t previous = NULL;

    while (ptr != NULL) {
        if (ptr->missile.id == id) {
            if (previous == NULL) {
                delete_last_missile_from_list(list);
            } else {
                previous->next = ptr->next;
                free(ptr);
            }
            break;
        }
        previous = ptr;
        ptr = ptr->next;
    }
}

void destroy_missile_list(missile_list_t* list)
{
    while (*list != NULL) {
        delete_last_missile_from_list(list);
    }
}

missile_t* get_missile_by_id(missile_list_t* list, int id)
{
    pt_missile_cell_t ptr = *list;

    while (ptr != NULL) {
        if (ptr->missile.id == id)
            return &(ptr->missile);
        ptr = ptr->next;
    }

    return NULL;
}

void order_list(missile_list_t* list)
{
    pt_missile_cell_t ptr = *list;
    int current = 0;

    while (ptr != NULL) {
        current++;
        ptr->missile.id = size_of_missile_list(list) - current;

        ptr = ptr->next;
    }
}

int size_of_missile_list(missile_list_t* list)
{
    pt_missile_cell_t ptr = *list;
    int size = 0;

    while (ptr != NULL) {
        size++;
        ptr = ptr->next;
    }

    return size;
}

void copy_client_list(missile_list_t* src, missile_list_t* dst)
{
    pt_missile_cell_t ptr = *src;

    while (ptr != NULL) {
        for (int i = 0; i < size_of_missile_list(src); i++) {
            append_missile_to_list(dst, &(ptr->missile));
        }
        ptr = ptr->next;
    }
}
