#include "libstr.h"

void init_str(String * str) {
    str->alloc   = 1;
    str->size    = 0;
    str->data    = malloc(sizeof(char));
    str->data[0] = '\0';
}

void destroy_str(String * str) {
    str->alloc = 0;
    str->size  = 0;
    free(str->data);
    str->data = NULL;
}

void clear_str(String * str) {
    str->alloc   = 1;
    str->size    = 0;
    str->data    = realloc(str->data, str->alloc * sizeof(char));
    str->data[0] = '\0';
}

void print_str(String * str) { printf("%s", str->data); }

void append_char_to_str(String * str, char c) {
    if (str->size + 1 >= str->alloc) {
        str->alloc++;
        str->data = realloc(str->data, str->alloc * sizeof(char));
    }

    str->data[str->size] = c;
    str->size++;
    str->data[str->size] = '\0';
}

void append_str_to_str(String * dst, char * src) {
    for (unsigned int i = 0; i < strlen(src); i++) {
        append_char_to_str(dst, src[i]);
    }
}

void set_str(String * dst, char * src) {
    clear_str(dst);
    append_str_to_str(dst, src);
}

char * to_string(String str) { return str.data; }
