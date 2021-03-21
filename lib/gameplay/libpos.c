/** Fichiers d'inclusions **/

#include "libpos.h"

/** Fonctions **/

void init_pos(pos_t* position)
{
    set_pos(position, 0, 0, 0, 0, 0, 0);
}

void set_pos(pos_t* position, float x, float y, float z, float dx, float dy, float dz)
{
    set_pos_x(position, x);
    set_pos_y(position, y);
    set_pos_z(position, z);
    set_pos_dx(position, dx);
    set_pos_dy(position, dy);
    set_pos_dz(position, dz);
}

void set_pos_x(pos_t* position, float x)
{
    position->x = x;
}

void set_pos_y(pos_t* position, float y)
{
    position->y = y;
}

void set_pos_z(pos_t* position, float z)
{
    position->z = z;
}

void set_pos_dx(pos_t* position, float dx)
{
    position->dx = dx;
}

void set_pos_dy(pos_t* position, float dy)
{
    position->dy = dy;
}

void set_pos_dz(pos_t* position, float dz)
{
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
