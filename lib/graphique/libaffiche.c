/**** Programme de creation de labyrinthe ****/

/** Fichiers d'inclusion **/

#include "libaffiche.h"

/* Soustraction de deux points */

point soustraire_points(point p1, point p2)
{
    point p;
    p.x = p1.x - p2.x;
    p.y = p1.y - p2.y;
    p.z = p1.z - p2.z;
    return p;
}

/* Copie les objets */

objet3D* duplique_objets(objet3D* objets, int nb)
{
    objet3D* copie = malloc(nb * sizeof(objet3D));
    memcpy(copie, objets, nb * sizeof(objet3D));
    return copie;
}

/* Compare la distance entre deux objets */

int compare_objets(const void* arg1, const void* arg2)
{
    const objet3D* objet1 = arg1;
    const objet3D* objet2 = arg2;
    int cx1 = 0;
    int cz1 = 0;
    int cx2 = 0;
    int cz2 = 0;

    if (objet1->type == TYPE_MUR) {
        cx1 = (objet1->p[0].x + objet1->p[3].x) / 2;
        cz1 = (objet1->p[0].z + objet1->p[3].z) / 2;
    } else if (objet1->type == TYPE_SPH) {
        cx1 = objet1->p[0].x;
        cz1 = objet1->p[0].z;
    } else {
        printf("objet1 could not be recognized during comparaison\n");
    }

    if (objet2->type == TYPE_MUR) {
        cx2 = (objet2->p[0].x + objet2->p[3].x) / 2;
        cz2 = (objet2->p[0].z + objet2->p[3].z) / 2;
    } else if (objet2->type == TYPE_SPH) {
        cx2 = objet2->p[0].x;
        cz2 = objet2->p[0].z;
    } else {
        printf("objet2 could not be recognized during comparaison\n");
    }

    int d1 = abs(cx1) + abs(cz1);
    int d2 = abs(cx2) + abs(cz2);

    return d2 - d1;
}

/* Tri des objets */

void tri_objets(objet3D* objets, int nb) { qsort(objets, nb, sizeof(objet3D), compare_objets); }

/* Calcul des objets en fonction du dessin */

int dessin_vers_objets(char* laby[], int largeur, int hauteur, objet3D* objets)
{
    int nb = 0;
    int i;
    // Labyrinthe de taille largeur x hauteur
    for (i = 0; i <= largeur; i++) {
        int j;
        for (j = 0; j <= hauteur; j++) {
            // Mur suivant l'axe x
            if (laby[2 * i][2 * j + 1] == '-') {
                objets[nb].type = TYPE_MUR;
                objets[nb].p[0].x = j * MUR_TAILLE;
                objets[nb].p[0].z = i * MUR_TAILLE;
                objets[nb].p[0].y = 0;
                objets[nb].p[1].x = j * MUR_TAILLE;
                objets[nb].p[1].z = i * MUR_TAILLE;
                objets[nb].p[1].y = MUR_HAUTEUR;
                objets[nb].p[2].x = (j + 1) * MUR_TAILLE;
                objets[nb].p[2].z = i * MUR_TAILLE;
                objets[nb].p[2].y = MUR_HAUTEUR;
                objets[nb].p[3].x = (j + 1) * MUR_TAILLE;
                objets[nb].p[3].z = i * MUR_TAILLE;
                objets[nb++].p[3].y = 0;
            }
            // Mur suivant l'axe z
            if (i < 8 && laby[2 * i + 1][2 * j] == '|') {
                objets[nb].type = TYPE_MUR;
                objets[nb].p[0].x = j * MUR_TAILLE;
                objets[nb].p[0].z = i * MUR_TAILLE;
                objets[nb].p[0].y = 0;
                objets[nb].p[1].x = j * MUR_TAILLE;
                objets[nb].p[1].z = i * MUR_TAILLE;
                objets[nb].p[1].y = MUR_HAUTEUR;
                objets[nb].p[2].x = j * MUR_TAILLE;
                objets[nb].p[2].z = (i + 1) * MUR_TAILLE;
                objets[nb].p[2].y = MUR_HAUTEUR;
                objets[nb].p[3].x = j * MUR_TAILLE;
                objets[nb].p[3].z = (i + 1) * MUR_TAILLE;
                objets[nb++].p[3].y = 0;
            }
        }
    }
    return nb;
}

void joueur_vers_objet(point* point, objet3D* objet)
{
    point_vers_objet(point, RAYON_JOUEUR, objet);
}

void tir_vers_objet(point* point, objet3D* objet)
{
    point_vers_objet(point, RAYON_TIR, objet);
}

void point_vers_objet(point* point, int rayon, objet3D* objet)
{
    objet->type = TYPE_SPH;
    objet->p[0].x = point->x;
    objet->p[0].y = point->y;
    objet->p[0].z = point->z;
    objet->p[1].x = rayon;
}

/* Translation par rapport a une position */

void decale_objets(objet3D* objets, int nb, point position)
{
    int i, j;
    for (i = 0; i < nb; i++) {
        switch (objets[i].type) {
        case TYPE_MUR:
            for (j = 0; j < 4; j++)
                objets[i].p[j] = soustraire_points(objets[i].p[j], position);
            break;
        case TYPE_SPH:
            objets[i].p[0] = soustraire_points(objets[i].p[0], position);
            break;
        }
    }
}

/* Rotation d'un labyrinthe */

void rotation_objets(objet3D* objets, int nb, int angle)
{
    int i, j, x, y, z;
    float radians = -2 * M_PI * angle / 360;
    for (i = 0; i < nb; i++) {
        switch (objets[i].type) {
        case TYPE_MUR:
            for (j = 0; j < 4; j++) {
                x = objets[i].p[j].x * cos(radians) + objets[i].p[j].z * sin(radians);
                y = objets[i].p[j].y;
                z = -objets[i].p[j].x * sin(radians) + objets[i].p[j].z * cos(radians);
                objets[i].p[j].x = x;
                objets[i].p[j].y = y;
                objets[i].p[j].z = z;
            }
            break;
        case TYPE_SPH:
            x = objets[i].p[0].x * cos(radians) + objets[i].p[0].z * sin(radians);
            y = objets[i].p[0].y;
            z = -objets[i].p[0].x * sin(radians) + objets[i].p[0].z * cos(radians);
            objets[i].p[0].x = x;
            objets[i].p[0].y = y;
            objets[i].p[0].z = z;
            break;
        }
    }
}

/* Test des collisions */

unsigned char collision_objets(objet3D* objets, int nb, point p, int r)
{
    int i, rayon;
    point p0, p1;
    for (i = 0; i < nb; i++) {
        switch (objets[i].type) {
        case TYPE_MUR:
            p0 = objets[i].p[0];
            p1 = objets[i].p[2];
            if (p.x >= p0.x - r && p.z >= p0.z - r && p.x <= p1.x + r && p.z <= p1.z + r)
                return 1;
            break;
        case TYPE_SPH:
            p0 = objets[i].p[0];
            rayon = objets[i].p[1].x;
            if ((p.x - p0.x) * (p.x - p0.x) + (p.z - p0.z) * (p.z - p0.z) <= r + rayon)
                return 1;
            break;
        }
    }
    return 0;
}

/* Projection en 2D */

void projete_objets(objet3D* src, int nb, objet2D* dst, int* no)
{
    int i, j;
    int x, y, z, x1, z1, x2, z2, r;
    *no = 0;
    for (i = 0; i < nb; i++) {
        switch (src[i].type) {
        case TYPE_MUR:
            x1 = src[i].p[0].x;
            z1 = src[i].p[0].z;
            x2 = src[i].p[3].x;
            z2 = src[i].p[3].z;

            if (z1 <= 0 && z2 <= 0)
                continue;
            if (z1 <= 0) {
                src[i].p[0].x = x2 + (x1 - x2) * (1 - z2) / (z1 - z2);
                src[i].p[0].z = 1;
                src[i].p[1].x = src[i].p[0].x;
                src[i].p[1].z = src[i].p[0].z;
            }
            if (z2 <= 0) {
                src[i].p[3].x = x1 + (x2 - x1) * (1 - z1) / (z2 - z1);
                src[i].p[3].z = 1;
                src[i].p[2].x = src[i].p[3].x;
                src[i].p[2].z = src[i].p[3].z;
            }

            dst[*no].type = TYPE_MUR;
            for (j = 0; j < 4; j++) {
                x = src[i].p[j].x;
                y = src[i].p[j].y;
                z = src[i].p[j].z;

                dst[*no].def.p[j].x = LARGEUR / 2 + x * FOCALE / z;
                dst[*no].def.p[j].y = HAUTEUR / 4 + (y - HAUTEUR / 4) * FOCALE / z;
            }
#ifdef DEBUG
            printf("[%d,%d,%d](%d,%d) ", x, y, z, px, py);
#endif
            break;
        case TYPE_SPH:
            x = src[i].p[0].x;
            y = src[i].p[0].y;
            z = src[i].p[0].z;
            r = src[i].p[1].x; // Rayon

            if (z <= 0)
                continue;

            dst[*no].type = TYPE_SPH;
            dst[*no].def.p->x = LARGEUR / 2 + x * FOCALE / z;
            /*
                calcul de y:
                a - b / z avec a,b > 0
                a = 18/23 * HAUTEUR             -> ligne d'horizon (z->+inf)
                b/z -> de HAUTEUR/2 à 0         -> niveau des yeux (z=1)
                zmin = 1 => b = 1/2 * HAUTEUR
            */
            dst[*no].def.p->y = 18 * HAUTEUR / 23 + (y - 1 * HAUTEUR / 2) / z;
            dst[*no].def.p[1].x = r * FOCALE / z; // Rayon
#ifdef DEBUG
            printf("[%d,%d,%d](%d,%d) ", x, y, z, px, py);
#endif
            break;
        }
        (*no)++;
#ifdef DEBUG
        printf("\n");
#endif
    }
}

/* Intersection d'un segment */

unsigned char inter_seg_v(point2D a, point2D b, int x, int* y)
{
    if (sign(a.x - x) == sign(b.x - x))
        return 0;
    *y = a.y + (b.y - a.y) * (x - a.x) / (b.x - a.x);
    return 1;
}

unsigned char inter_seg_h(point2D a, point2D b, int* x, int y)
{
    if (sign(a.y - y) == sign(b.y - y))
        return 0;
    *x = a.x + (b.x - a.x) * (y - a.y) / (b.y - a.y);
    return 1;
}

/* Intersection d'un polygone avec un rectangle */

void inter_poly_rect(point2D* orig, int no, point2D* result, int* nr)
{
    point2D avant[POINTS_MAX];
    point2D apres[POINTS_MAX];
    int i, j;
    for (i = 0; i < no; i++)
        avant[i] = orig[i];
#ifdef DEBUG
    printf("??");
    for (i = 0; i < no; i++)
        printf("(%d,%d) ", avant[i].x, avant[i].y);
    printf("\n");
#endif
    int nv = no;
    for (i = 0; i < 4; i++) {
        int np = 0;
        for (j = 0; j < nv; j++) {
            int p = (j + nv - 1) % nv;
            point2D a = avant[p];
            point2D b = avant[j];
            int x, y;
            unsigned char inta, intb;
            switch (i) {
            case 0:
                x = 0;
                inter_seg_v(a, b, x, &y);
                if (a.x >= 0)
                    inta = 1;
                else
                    inta = 0;
                if (b.x >= 0)
                    intb = 1;
                else
                    intb = 0;
                break;
            case 1:
                y = HAUTEUR;
                inter_seg_h(a, b, &x, y);
                if (a.y <= HAUTEUR)
                    inta = 1;
                else
                    inta = 0;
                if (b.y <= HAUTEUR)
                    intb = 1;
                else
                    intb = 0;
                break;
            case 2:
                x = LARGEUR;
                inter_seg_v(a, b, x, &y);
                if (a.x <= LARGEUR)
                    inta = 1;
                else
                    inta = 0;
                if (b.x <= LARGEUR)
                    intb = 1;
                else
                    intb = 0;
                break;
            case 3:
                y = 0;
                inter_seg_h(a, b, &x, y);
                if (a.y >= 0)
                    inta = 1;
                else
                    inta = 0;
                if (b.y >= 0)
                    intb = 1;
                else
                    intb = 0;
                break;
            }
            if (intb) {
                if (!inta) {
                    apres[np].x = x;
                    apres[np].y = y;
                    np++;
                }
                apres[np++] = b;
            } else {
                if (inta) {
                    apres[np].x = x;
                    apres[np].y = y;
                    np++;
                }
            }
        }
        for (j = 0; j < np; j++)
            avant[j] = apres[j];
        nv = np;
    }
    for (i = 0; i < nv; i++)
        result[i] = avant[i];
#ifdef DEBUG
    printf("!!");
    for (i = 0; i < nv; i++)
        printf("(%d,%d) ", result[i].x, result[i].y);
    printf("\n");
#endif
    *nr = nv;
}

/* Dessin du labyrinthe */

void dessine_2D(objet2D* objets, int no)
{
    int i, j;
    short int x[POINTS_MAX];
    short int y[POINTS_MAX];
    for (i = 0; i < no; i++) {
        if (objets[i].type == TYPE_MUR) {
            point2D poly[POINTS_MAX];
            int np;
            inter_poly_rect(objets[i].def.p, 4, poly, &np);
            for (j = 0; j < np; j++) {
                x[j] = poly[j].x;
                y[j] = HAUTEUR - poly[j].y;
            }
            polygonePlein(x, y, np, COULEUR_ROUGE, COULEUR_ROSE);
        }
        if (objets[i].type == TYPE_SPH) {
            int rayon = objets[i].def.p[1].x; // Rayon
            disque(objets[i].def.p->x, objets[i].def.p->y, rayon, COULEUR_BLANC, COULEUR_ROSE);
        }
    }
}
