/**** Bibliotheque des listes de chaines de caracteres ****/

#ifndef _LIBSTRLIST_H_
#define _LIBSTRLIST_H_

/** Fichiers d'inclusion des bibliotheques **/

#include "libstr.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/** Constantes **/

/** Variables **/

typedef struct ListStr ListStr;
struct ListStr {
    String * str_list;
    int      size;
    int      alloc;
};

/** Prototypes **/

void init_list_str(ListStr * list);

void destroy_list_str(ListStr * list);

void clear_list(ListStr * list);

void append_str_to_list(ListStr * list, char * str);

#endif
