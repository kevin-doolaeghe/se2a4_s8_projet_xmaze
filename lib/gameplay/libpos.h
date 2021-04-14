/**** Bibliotheque de positions  ****/

#ifndef _LIBPOS_H_
#define _LIBPOS_H_

/** Fichiers d'inclusion des bibliothèques **/

#include <stdio.h>

/** Constantes **/

/** Variables **/

typedef struct pos_s pos_t;
struct pos_s {
    int x;
    int y;
    int z;
    int angle;
};

/** Prototypes **/

void init_pos(pos_t* position);
void set_pos(pos_t* position, int x, int y, int z, int angle);
void copy_pos(pos_t* dst, pos_t* src);
void print_pos(pos_t* position);

#endif
