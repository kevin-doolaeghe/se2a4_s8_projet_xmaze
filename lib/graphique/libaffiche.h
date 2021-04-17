/**** Bibliotheque de constantes graphique ****/

#ifndef _LIBAFFICHE_H_
#define _LIBAFFICHE_H_

/** Fichiers d'inclusion des bibliotheques **/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "libgraph.h"

/** Constantes **/

#define TITRE "Shooter Labyrinthe"
#define LARGEUR 1280
#define HAUTEUR 720

#define LABY_X 8
#define LABY_Y 8
#define MUR_TAILLE 200
#define MUR_HAUTEUR 200

#define FOCALE (3 * MUR_TAILLE)

#define ATTENTE 10000

#define POINTS_MAX 32

#define TYPE_MUR 0

/** Macros **/

#define max(a, b) (((a) < (b)) ? (a) : (b))
#define min(a, b) (((a) > (b)) ? (b) : (a))
#define sign(a) (((a) == 0) ? 0 : (((a) > 0) ? 1 : -1))

/** Types **/

typedef struct {
    int x, y, z;
} point;

typedef struct {
    int x, y;
} point2D;

typedef struct {
    point p[4];
} mur;

typedef struct {
    int type;
    union {
        point2D p[4];
    } def;
} objet2D;

/** Fonctions **/

point soustraire_points(point p1, point p2);
mur* duplique_murs(mur* murs, int nb);
int compare_murs(const void* arg1, const void* arg2);
void tri_murs(mur* murs, int n);
int dessin_vers_murs(char* laby[], mur* murs);
void decale_murs(mur* murs, int nb, point position);
void rotation_murs(mur* murs, int nb, int angle);
void projete_murs(mur* murs, int nb, objet2D* objets, int* no);
unsigned char inter_seg_v(point2D a, point2D b, int x, int* y);
unsigned char inter_seg_h(point2D a, point2D b, int* x, int y);
void inter_poly_rect(point2D* orig, int no, point2D* result, int* nr);
void dessine_2D(objet2D* objet, int no);

#endif