/**** Bibliotheque table des clients  ****/

#ifndef _LIBPOS_H_
#define _LIBPOS_H_

/** Fichiers d'inclusion des bibliothèques **/

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>

/** Constantes **/


/** Variables **/

typedef struct pos_s pos_t;
struct pos_s {
    float x;
    float y;
    float z;
    float x_vec;
    float y_vec;
    float z_vec;
};

/** Prototypes **/


#endif
