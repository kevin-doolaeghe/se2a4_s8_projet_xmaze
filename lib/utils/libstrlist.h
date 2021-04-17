/**** Bibliotheque des listes de chaines de caracteres ****/

#ifndef _LIBSTRLIST_H_
#define _LIBSTRLIST_H_

/** Fichiers d'inclusion des bibliotheques **/

#include "libstr.h"

/** Variables **/

typedef struct str_list_s str_list_t;
struct str_list_s {
    str_t* str_list;
    int size;
    int alloc;
};

/** Prototypes **/

void init_str_list(str_list_t* list);
void destroy_str_list(str_list_t* list);
void clear_str_list(str_list_t* list);
void append_cstr_to_list(str_list_t* list, char* str);
void append_str_to_list(str_list_t* list, str_t* str);
void split_cstr_to_str_list(str_list_t* list, const char* delim, char* str);
void copy_str_list(str_list_t* dst, str_list_t* src);
void print_str_list(str_list_t* list);

#endif
