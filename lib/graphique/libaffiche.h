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

#define MUR_TAILLE 200
#define MUR_HAUTEUR 200
#define RAYON_TIR 10
#define RAYON_JOUEUR 15

#define FOCALE (2 * MUR_TAILLE)

#define ATTENTE 10000

#define POINTS_MAX 64

#define TYPE_MUR 0
#define TYPE_SPH 1

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
        int rayon;
    } def;
} objet2D;

/** Fonctions **/

point soustraire_points(point p1, point p2);

mur* duplique_murs(mur* murs, int nb);
int compare_murs(const void* arg1, const void* arg2);
void tri_murs(mur* murs, int n);

int dessin_vers_murs(char* laby[], mur* murs);

void decale_murs(mur* murs, int nb, point position);
void decale_points(point* points, int nb, point position);

void rotation_murs(mur* murs, int nb, int angle);
void rotation_points(point* points, int nb, int angle);

void projete_murs(mur* murs, int nb, objet2D* objets, int* no);
void projete_joueur(point* points, int nb, objet2D* objets, int* no);
void projete_tir(point* points, int nb, objet2D* objets, int* no);
void projete_sphere(point* points, int nb, int rayon, objet2D* objets, int* no);

unsigned char inter_seg_v(point2D a, point2D b, int x, int* y);
unsigned char inter_seg_h(point2D a, point2D b, int* x, int y);
void inter_poly_rect(point2D* orig, int no, point2D* result, int* nr);

void dessine_2D(objet2D* objet, int no);

unsigned char collision_murs(mur* murs, int nb, point p, int r);
unsigned char collision_sphere(point pa, int ra, point pb, int rb);

#endif