/**** Bibliotheque des clients  ****/

#ifndef _LIBMISSILE_H_
#define _LIBMISSILE_H_

/** Fichiers d'inclusion des bibliotheques **/

#include "libpos.h"

/** Types **/

typedef struct missile_s missile_t;
struct missile_s {
    int id;
    pos_t position;
    int tireur;
};

/** Prototypes **/

void init_missile(missile_t* missile);
void set_missile(missile_t* missile, int id, pos_t* position, int tireur);
void set_missile_id(missile_t* missile, int id);
void set_missile_position(missile_t* missile, pos_t* position);
void set_missile_tireur(missile_t* missile, int tireur);

#endif
