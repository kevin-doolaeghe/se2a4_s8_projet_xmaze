/** Fichiers d'inclusions **/

#include "libstr.h"

/** Fonctions **/

void init_str(str_t* str)
{
    str->alloc = 1;
    str->size = 0;
    str->data = malloc(sizeof(char));
    str->data[0] = '\0';
}

void destroy_str(str_t* str)
{
    str->alloc = 0;
    str->size = 0;
    free(str->data);
    str->data = NULL;
}

void clear_str(str_t* str)
{
    str->alloc = 1;
    str->size = 0;
    str->data = realloc(str->data, str->alloc * sizeof(char));
    str->data[0] = '\0';
}

void append_char_to_str(str_t* str, char c)
{
    if (str->size + 1 >= str->alloc) {
        str->alloc++;
        str->data = realloc(str->data, str->alloc * sizeof(char));
    }

    str->data[str->size] = c;
    str->size++;
    str->data[str->size] = '\0';
}

void append_cstr_to_str(str_t* dst, char* src)
{
    for (unsigned int i = 0; i < strlen(src); i++) {
        append_char_to_str(dst, src[i]);
    }
}

void append_str_to_str(str_t* dst, str_t* src)
{
    append_cstr_to_str(dst, src->data);
}

void set_str_from_cstr(str_t* dst, char* src)
{
    clear_str(dst);
    append_cstr_to_str(dst, src);
}

void set_str_from_str(str_t* dst, str_t* src)
{
    set_str_from_cstr(dst, src->data);
}

int compare_str(str_t* str1, str_t* str2)
{
    return strcmp(str1->data, str2->data);
}

void print_str(str_t* str) { printf("%s", str->data); }

char* to_cstr(str_t* str) { return str->data; }
