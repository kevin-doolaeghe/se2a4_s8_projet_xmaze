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
#define RAYON_JOUEUR 20

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
    int type;
    point p[4];
} objet3D;

typedef struct {
    int type;
    union {
        point2D p[4];
    } def;
} objet2D;

/** Fonctions **/

point soustraire_points(point p1, point p2);

objet3D* duplique_objets(objet3D* objets, int nb);

int compare_objets(const void* arg1, const void* arg2);
void tri_objets(objet3D* objets, int nb);

int dessin_vers_objets(char* laby[], int largeur, int hauteur, objet3D* objets);
void joueur_vers_objet(point* point, objet3D* objet);
void tir_vers_objet(point* point, objet3D* objet);
void point_vers_objet(point* point, int rayon, objet3D* objet);

void decale_objets(objet3D* objets, int nb, point position);
void rotation_objets(objet3D* objets, int nb, int angle);

unsigned char collision_objets(objet3D* objets, int nb, point p, int r);

void projete_objets(objet3D* src, int nb, objet2D* dst, int* no);

unsigned char inter_seg_v(point2D a, point2D b, int x, int* y);
unsigned char inter_seg_h(point2D a, point2D b, int* x, int y);
void inter_poly_rect(point2D* orig, int no, point2D* result, int* nr);

void dessine_2D(objet2D* objet, int no);

#endif