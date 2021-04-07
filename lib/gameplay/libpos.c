/** Fichiers d'inclusions **/

#include "libpos.h"

/** Fonctions **/

void init_pos(pos_t* position)
{
    set_pos(position, 0, 0, 0, 0, 0, 0);
}

void set_pos(pos_t* position, int x, int y, int z, int dx, int dy, int dz)
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
    printf("x: %d\n", position->x);
    printf("y: %d\n", position->y);
    printf("z: %d\n", position->z);
    printf("dx: %d\n", position->dx);
    printf("dy: %d\n", position->dy);
    printf("dz: %d\n", position->dz);
}
