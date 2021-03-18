/**** Bibliotheque des chaines de caracteres ****/

#ifndef _LIBSTR_H_
#define _LIBSTR_H_

/** Fichiers d'inclusion des bibliothèques **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/** Constantes **/

/** Variables **/

typedef struct String String;
struct String {
    char* data;
    int size;
    int alloc;
};

/** Prototypes **/

void init_str(String* str);

void destroy_str(String* str);

void clear_str(String* str);

void print_str(String* str);

void append_char_to_str(String* str, char c);

void append_str_to_str(String* dst, char* src);

void set_str(String* dst, char* src);

char* to_string(String str);

#endif
