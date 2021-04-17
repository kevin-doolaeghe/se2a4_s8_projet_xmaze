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

void append_cstr_to_list(str_list_t* list, char* str)
{
    if (list->size + 1 > list->alloc) {
        list->alloc++;
        list->str_list = realloc(list->str_list, list->alloc * sizeof(str_t));
        init_str(&(list->str_list[list->alloc - 1]));
    }

    set_str_from_cstr(&(list->str_list[list->size]), str);
    list->size++;
}

void append_str_to_list(str_list_t* list, str_t* str)
{
    append_cstr_to_list(list, str->data);
}

void split_cstr_to_str_list(str_list_t* list, const char* delim, char* str)
{
    clear_str_list(list);

    int i;
    char* tmp = NULL;
    char* token = NULL;

    for (i = 0, tmp = str;; i++, tmp = NULL) {
        token = strtok(tmp, delim);
        if (token == NULL) {
            break;
        }
        append_cstr_to_list(list, token);
    }
}

void copy_str_list(str_list_t* dst, str_list_t* src)
{
    for (int i = 0; i < src->alloc; i++) {
        append_str_to_list(dst, &(src->str_list[i]));
    }
}

void print_str_list(str_list_t* list)
{
    for (int i = 0; i < list->alloc; i++) {
        print_str(&(list->str_list[i]));
        printf("\n");
    }
}
