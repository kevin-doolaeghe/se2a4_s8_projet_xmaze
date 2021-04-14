/** Fichiers d'inclusions **/

#include "libpos.h"

/** Fonctions **/

void init_pos(pos_t* position)
{
    set_pos(position, 0, 0, 0, 0);
}

void set_pos(pos_t* position, int x, int y, int z, int angle)
{
    position->x = x;
    position->y = y;
    position->z = z;
    position->angle = angle;
}

void copy_pos(pos_t* dst, pos_t* src)
{
    dst->x = src->x;
    dst->y = src->y;
    dst->z = src->z;
    dst->angle = src->angle;
}

void print_pos(pos_t* position)
{
    printf("x: %d\n", position->x);
    printf("y: %d\n", position->y);
    printf("z: %d\n", position->z);
    printf("angle: %d\n", position->angle);
}
