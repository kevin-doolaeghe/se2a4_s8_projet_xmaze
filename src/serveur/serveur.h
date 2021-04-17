/**** Header serveur ****/

#ifndef _SERVEUR_H_
#define _SERVEUR_H_

/** Fichiers d'inclusion des bibliothèques **/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "chat.h"
#include "diffusion.h"
#include "graphiques.h"
#include "libaffiche.h"
#include "libclientlist.h"
#include "libsig.h"
#include "libthread.h"
#include "touches.h"

/** Variables **/

client_list_t client_list;

bool quitter_serveur;
bool partie_en_cours;

mur murs[(LABY_X + 1) * LABY_Y + (LABY_Y + 1) * LABY_X];
char* laby[2 * LABY_Y + 1] = {
    " - - - - - - - - ", "|. . . . . . . .|", "                 ",
    "|. .|. . . . . .|", "       - -       ", "|. .|.|. .|. . .|",
    "                 ", "|. .|.|. .|. . .|", "                 ",
    "|. .|.|. .|. . .|", "       - -       ", "|. .|.|. . . . .|",
    "                 ", "|. .|.|. . . . .|", "                 ",
    "|. . . . . . . .|", " - - - - - - - - "
};
int nb;

/** Prototypes **/

int main(int argc, char* argv[]);
void usage();
void init_serveur();
void detruire_serveur();

#endif
