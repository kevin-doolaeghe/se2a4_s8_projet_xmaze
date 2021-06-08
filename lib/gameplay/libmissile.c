/** Fichiers d'inclusions **/

#include "libmissile.h"

/** Fonctions **/

void init_missile(missile_t* missile)
{
    missile->tir = -1;
    init_pos(&(missile->position));
}

void set_missile(missile_t* missile, int tir, pos_t* position)
{
    set_missile_tir(missile, tir);
    set_missile_position(missile, position);
}

void set_missile_tir(missile_t* missile, int tir)
{
    missile->tir = tir;
}

void set_missile_position(missile_t* missile, pos_t* position)
{
    copy_pos(&(missile->position), position);
}

void copy_missile(missile_t* dst, missile_t* src)
{
    dst->tir = src->tir;
    copy_pos(&(src->position), &(src->position));
}