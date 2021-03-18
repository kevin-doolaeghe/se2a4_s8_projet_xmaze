/**** Bibliotheque de positions  ****/

#ifndef _LIBPOS_H_
#define _LIBPOS_H_

/** Fichiers d'inclusion des bibliothèques **/

#include <stdio.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/types.h>

/** Constantes **/

/** Variables **/

typedef struct pos_s pos_t;
struct pos_s {
    float x;
    float y;
    float z;
    float x_vec;
    float y_vec;
    float z_vec;
};

/** Prototypes **/

void init_pos(pos_t* position);
void print_pos(pos_t* position);
void set_pos(pos_t* dst, pos_t* src);

#endif
