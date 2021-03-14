/**** Bibliotheque client ****/

/** Fichiers d'inclusions **/

#include "libpos.h"

/** Fonctions **/

void init_pos(pos_t *position) {
    position->x = 0;
    position->y = 0;
    position->z = 0;
    position->x_vec = 0;
    position->y_vec = 0;
    position->z_vec = 0;
}

void print_pos(pos_t *position) {
    printf("position:\n");
    printf("\tx: %f\n", position->x);
    printf("\ty: %f\n", position->y);
    printf("\tz: %f\n", position->z);
    printf("\tx_vec: %f\n", position->x_vec);
    printf("\ty_vec: %f\n", position->y_vec);
    printf("\tz_vec: %f\n", position->z_vec);
}

void set_pos(pos_t *dst, pos_t *src) {
    dst->x = src->x;
    dst->y = src->y;
    dst->z = src->z;
    dst->x_vec = src->x_vec;
    dst->y_vec = src->y_vec;
    dst->z_vec = src->z_vec;
}