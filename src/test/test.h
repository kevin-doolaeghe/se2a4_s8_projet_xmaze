#ifndef _TEST_H_
#define _TEST_H_

/** Fichiers d'inclusion **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "libaffiche.h"

/** Constantes **/

/** Macros **/

/** Structures **/

/** Variables globales **/

mur murs[(LABY_X + 1) * LABY_Y + (LABY_Y + 1) * LABY_X];

char* laby[2 * LABY_Y + 1] = { " - - - - - - - - ", "|. . . . . . . .|", "                 ",
    "|. .|. . . . . .|", "       - -       ", "|. .|.|. .|. . .|",
    "                 ", "|. .|.|. .|. . .|", "                 ",
    "|. .|.|. .|. . .|", "       - -       ", "|. .|.|. . . . .|",
    "                 ", "|. .|.|. . . . .|", "                 ",
    "|. . . . . . . .|", " - - - - - - - - " };

/** Fonctions **/

void jeu();
int main(void);

#endif