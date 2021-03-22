/** Fichiers d'inclusions **/

#include "libpos.h"

/** Fonctions **/

void init_pos(pos_t* position)
{
    set_pos(position, 0, 0, 0, 0, 0, 0);
}

void set_pos(pos_t* position, float x, float y, float z, float dx, float dy, float dz)
{
    position->x = x;
    position->y = y;
    position->z = z;
    position->dx = dx;
    position->dy = dy;
    position->dz = dz;
}

void copy_pos(pos_t* dst, pos_t* src)
{
    dst->x = src->x;
    dst->y = src->y;
    dst->z = src->z;
    dst->dx = src->dx;
    dst->dy = src->dy;
    dst->dz = src->dz;
}

void print_pos(pos_t* position)
{
    printf("x: %f\n", position->x);
    printf("y: %f\n", position->y);
    printf("z: %f\n", position->z);
    printf("dx: %f\n", position->dx);
    printf("dy: %f\n", position->dy);
    printf("dz: %f\n", position->dz);
}
