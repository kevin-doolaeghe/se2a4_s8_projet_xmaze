/**** Bibliotheque des chaines de caracteres ****/

#ifndef _LIBSTR_H_
#define _LIBSTR_H_

/** Fichiers d'inclusion des bibliothèques **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/** Constantes **/

/** Variables **/

typedef struct str_s str_t;
struct str_s {
    char* data;
    int size;
    int alloc;
};

/** Prototypes **/

void init_str(str_t* str);
void destroy_str(str_t* str);
void clear_str(str_t* str);
void append_char_to_str(str_t* str, char c);
void append_cstr_to_str(str_t* dst, char* src);
void append_str_to_str(str_t* dst, str_t* src);
void set_str_from_cstr(str_t* dst, char* src);
void set_str_from_str(str_t* dst, str_t* src);
int compare_str(str_t* str1, str_t* str2);
void print_str(str_t* str);
char* to_cstr(str_t* str);

#endif
