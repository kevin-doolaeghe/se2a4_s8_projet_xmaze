#include "libstrlist.h"

void init_list_str(ListStr* list)
{
    list->alloc = 1;
    list->size = 0;
    list->str_list = malloc(sizeof(String));
    init_str(&(list->str_list[0]));
}

void destroy_list_str(ListStr* list)
{
    for (int i = 0; i < list->alloc; i++) {
        destroy_str(&(list->str_list[i]));
    }
    list->alloc = 0;
    list->size = 0;
    free(list->str_list);
    list->str_list = NULL;
}

void clear_list(ListStr* list)
{
    for (int i = 0; i < list->alloc; i++) {
        destroy_str(&(list->str_list[i]));
    }
    list->alloc = 1;
    list->size = 0;
    list->str_list = realloc(list->str_list, list->alloc * sizeof(String));
    init_str(&(list->str_list[0]));
}

void append_str_to_list(ListStr* list, char* str)
{
    if (list->size + 1 > list->alloc) {
        list->alloc++;
        list->str_list = realloc(list->str_list, list->alloc * sizeof(String));
        init_str(&(list->str_list[list->alloc - 1]));
    }

    set_str(&(list->str_list[list->size]), str);
    list->size++;
}
