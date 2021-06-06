/**** Bibliotheque de la table des clients  ****/

#ifndef _LIBMISSILELIST_H_
#define _LIBMISSILELIST_H_

/** Fichiers d'inclusion des bibliotheques **/

#include <stdbool.h>
#include <stdlib.h>

#include "libmissile.h"

/** Types **/

typedef struct missile_cell_s missile_cell_t;
struct missile_cell_s {
    missile_t missile;
    missile_cell_t* next;
};

typedef missile_cell_t* missile_list_t;
typedef missile_cell_t* pt_missile_cell_t;

/** Prototypes **/

pt_missile_cell_t allocate_missile(missile_t* missile);
void append_missile_to_list(missile_list_t* list, missile_t* missile);
void delete_last_missile_from_list(missile_list_t* list);
void delete_missile_from_list(missile_list_t* list, int id);
void destroy_missile_list(missile_list_t* list);
missile_t* get_missile_by_id(missile_list_t* list, int id);
void order_list(missile_list_t* list);
int size_of_missile_list(missile_list_t* list);
void copy_client_list(missile_list_t* src, missile_list_t* dst);

#endif
