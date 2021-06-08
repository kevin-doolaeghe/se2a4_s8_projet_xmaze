/**** Bibliotheque des clients  ****/

#ifndef _LIBMISSILE_H_
#define _LIBMISSILE_H_

/** Fichiers d'inclusion des bibliotheques **/

#include "libpos.h"

/** Constantes **/

#define TIR_ACTIF 1
#define TIR_INACTIF 0

/** Types **/

typedef struct missile_s missile_t;
struct missile_s {
    int tir;
    pos_t position;
};

/** Prototypes **/

void init_missile(missile_t* missile);
void set_missile(missile_t* missile, int tir, pos_t* position);
void set_missile_tir(missile_t* missile, int tir);
void set_missile_position(missile_t* missile, pos_t* position);
void copy_missile(missile_t* dst, missile_t* src);

#endif
