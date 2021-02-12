#ifndef _LIBSTRLIST_H_
#define _LIBSTRLIST_H_

#include "str.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ListStr ListStr;
struct ListStr {
    String * str_list;
    int      size;
    int      alloc;
};

//----------------------------------------------

void init_list_str(ListStr * list);

void destroy_list_str(ListStr * list);

void clear_list(ListStr * list);

void append_str_to_list(ListStr * list, char * str);

#endif
