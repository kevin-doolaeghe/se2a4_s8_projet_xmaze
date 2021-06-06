/** Fichiers d'inclusions **/

#include "libmissile.h"

/** Fonctions **/

void init_missile(missile_t* missile)
{
    missile->id = -1;
    init_pos(&(missile->position));
    missile->tireur = -1;
}

void set_missile(missile_t* missile, int id, pos_t* position, int tireur)
{
    set_missile_id(missile, id);
    set_missile_position(missile, position);
    set_missile_tireur(missile, tireur);
}

void set_missile_id(missile_t* missile, int id)
{
    missile->id = id;
}

void set_missile_position(missile_t* missile, pos_t* position)
{
    copy_pos(&(missile->position), position);
}

void set_missile_tireur(missile_t* missile, int tireur)
{
    missile->tireur = tireur;
}
