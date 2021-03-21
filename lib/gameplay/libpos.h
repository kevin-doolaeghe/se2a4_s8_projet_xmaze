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
void set_pos_x(pos_t* position, float x);
void set_pos_y(pos_t* position, float y);
void set_pos_z(pos_t* position, float z);
void set_pos_dx(pos_t* position, float dx);
void set_pos_dy(pos_t* position, float dy);
void set_pos_dz(pos_t* position, float dz);
void copy_pos(pos_t* dst, pos_t* src);
void print_pos(pos_t* position);

#endif
