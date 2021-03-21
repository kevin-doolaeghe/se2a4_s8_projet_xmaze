/** Fichiers d'inclusions **/

#include "libstrlist.h"

/** Fonctions **/

void init_str_list(str_list_t* list)
{
    list->alloc = 1;
    list->size = 0;
    list->str_list = malloc(sizeof(str_t));
    init_str(&(list->str_list[0]));
}

void destroy_str_list(str_list_t* list)
{
    for (int i = 0; i < list->alloc; i++) {
        destroy_str(&(list->str_list[i]));
    }
    list->alloc = 0;
    list->size = 0;
    free(list->str_list);
    list->str_list = NULL;
}

void clear_str_list(str_list_t* list)
{
    for (int i = 0; i < list->alloc; i++) {
        destroy_str(&(list->str_list[i]));
    }
    list->alloc = 1;
    list->size = 0;
    list->str_list = realloc(list->str_list, list->alloc * sizeof(str_t));
    init_str(&(list->str_list[0]));
}

void append_str_to_list(str_list_t* list, char* str)
{
    if (list->size + 1 > list->alloc) {
        list->alloc++;
        list->str_list = realloc(list->str_list, list->alloc * sizeof(str_t));
        init_str(&(list->str_list[list->alloc - 1]));
    }

    set_str(&(list->str_list[list->size]), str);
    list->size++;
}

void copy_str_list(str_list_t* dst, str_list_t* src)
{
    for (int i = 0; i < src->alloc; i++) {
        append_str_to_list(dst, src->str_list[i].data);
    }
}

void print_str_list(str_list_t* list)
{
    for (int i = 0; i < list->alloc; i++) {
        print_str(&(list->str_list[i]));
        printf("\n");
    }
}
