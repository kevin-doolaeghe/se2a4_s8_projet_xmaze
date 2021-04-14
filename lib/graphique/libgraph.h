/**** Bibliotheque graphique ****/

#ifndef _LIBGRAPH_H_
#define _LIBGRAPH_H_

/** Fichiers d'inclusion des bibliothèques **/

#include "SDL2/SDL.h"
#include "SDL2/SDL2_gfxPrimitives.h"

/** Constantes **/

#define COULEUR_BLANC 0
#define COULEUR_NOIR 1
#define COULEUR_ROUGE 2
#define COULEUR_VERT 3
#define COULEUR_BLEU 4
#define COULEUR_ROSE 5

#define TOUCHE_DROITE '>'
#define TOUCHE_GAUCHE '<'
#define TOUCHE_HAUT '^'
#define TOUCHE_BAS 'v'
#define TOUCHE_ESPACE ' '
#define TOUCHE_AUTRE -1

/** Types **/

typedef struct {
    int r, v, b;
} couleur;

/** Constantes **/

#define BITS_PAR_PIXEL 32

/** Macros **/

#define GFX_COULEUR(r, v, b) (((((r << 8) | v) << 8) | b) << 8 | 0xff)

/** Prototypes **/

unsigned char creerFenetre(int largeur, int hauteur, char* titre);
void fermerFenetre(void);
void effacerFenetre(void);
void synchroniserFenetre(void);
void polygonePlein(short int* x, short int* y, int n, int c_int, int c_ext);
void rectanglePlein(int x, int y, int l, int h, int c_int, int c_ext);
void disque(int x, int y, int r, int c_int, int c_ext);
void appliquerDessins(void);
unsigned char attendreEvenement(int* touche, unsigned char* fenetre, unsigned char* quitter);
unsigned char sauverSurface(char* fichier);
unsigned char chargerSurface(char* fichier);

#endif