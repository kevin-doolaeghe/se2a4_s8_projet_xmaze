/**** Bibliotheque de positions  ****/

#ifndef _LIBPOS_H_
#define _LIBPOS_H_

/** Fichiers d'inclusion des bibliothèques **/

#include <stdio.h>

/** Constantes **/

/** Variables **/

typedef struct pos_s pos_t;
struct pos_s {
    float x;
    float y;
    float z;
    float dx;
    float dy;
    float dz;
};

/** Prototypes **/

void init_pos(pos_t* position);
void set_pos(pos_t* position, float x, float y, float z, float dx, float dy, float dz);
void copy_pos(pos_t* dst, pos_t* src);
void print_pos(pos_t* position);

#endif
