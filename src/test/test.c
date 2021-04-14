/** Fichiers d'inclusion **/

#include "test.h"

/** Fonctions **/

void init()
{
    nb = dessin_vers_murs(laby, murs);

    p.x = LABY_X / 2 * MUR_TAILLE;
    p.y = 0;
    p.z = MUR_TAILLE;

    angle = 0;
}

void affiche(objet2D* objets, int no)
{
    effacerFenetre();
    dessine_2D(objets, no);
    synchroniserFenetre();
}

void calcul(int touche)
{
    if (touche) {
        if (touche == TOUCHE_DROITE)
            angle += 5;
        if (touche == TOUCHE_GAUCHE)
            angle -= 5;
        if (angle < 0 || angle > 360)
            angle = angle % 360;
        if (touche == TOUCHE_HAUT) {
            p.x += MUR_TAILLE / 10 * sin(2 * M_PI * angle / 360);
            p.z += MUR_TAILLE / 10 * cos(2 * M_PI * angle / 360);
        }
        if (touche == TOUCHE_BAS) {
            p.x -= MUR_TAILLE / 10 * sin(2 * M_PI * angle / 360);
            p.z -= MUR_TAILLE / 10 * cos(2 * M_PI * angle / 360);
        }
    }

    mur* m2 = duplique_murs(murs, nb);
    decale_murs(m2, nb, p);
    rotation_murs(m2, nb, angle);
    tri_murs(m2, nb);
    objet2D* objets = malloc(nb * sizeof(objet2D));
    int no;
    projete_murs(m2, nb, objets, &no);

    affiche(objets, no);

    free(m2);
    free(objets);
}

void touches()
{
    unsigned char resultat = creerFenetre(LARGEUR, HAUTEUR, TITRE);
    if (!resultat) {
        fprintf(stderr, "Problème graphique !\n");
        exit(-1);
    }

    int touche;
    unsigned char fenetre, quitter;
    while (1) {
        int evenement = attendreEvenement(&touche, &fenetre, &quitter);
        if (!evenement) {
            usleep(ATTENTE);
            continue;
        }

        if (quitter == 1)
            break;

        if (touche || fenetre) {
            calcul(touche);
        }
    }
    fermerFenetre();
}

void jeu()
{
    unsigned char resultat = creerFenetre(LARGEUR, HAUTEUR, TITRE);
    if (!resultat) {
        fprintf(stderr, "Problème graphique !\n");
        exit(-1);
    }

    int touches;
    int x, y, dx, dy;
    int quitter = 0;

    int ellapsed_time;
    int start_time;
    SDL_Event event;
    while (1) {
        start_time = SDL_GetTicks();
        SDL_PollEvent(&event);
        touches = 0;

        /* Evenements */
        switch (event.type) {
        case SDL_WINDOWEVENT:
            SDL_Log("window");
            switch (event.window.event) {
            case SDL_WINDOWEVENT_CLOSE:
                SDL_Log("+close");
                quitter = 1;
                break;
            case SDL_WINDOWEVENT_LEAVE:
            case SDL_WINDOWEVENT_FOCUS_LOST:
                SDL_Log("+pause");
                break;
            case SDL_WINDOWEVENT_ENTER:
            case SDL_WINDOWEVENT_FOCUS_GAINED:
                SDL_Log("+resume");
                break;
            }
            break;
        case SDL_QUIT:
            SDL_Log("+quit");
            quitter = 1;
            break;
        case SDL_KEYDOWN:
            SDL_Log("+key");
            if (event.key.keysym.scancode == SDL_SCANCODE_W) {
                SDL_Log("+up");
            }
            if (event.key.keysym.scancode == SDL_SCANCODE_S) {
                SDL_Log("+down");
            }
            if (event.key.keysym.scancode == SDL_SCANCODE_A) {
                SDL_Log("+left");
            }
            if (event.key.keysym.scancode == SDL_SCANCODE_D) {
                SDL_Log("+right");
            }
            if (event.key.keysym.scancode == SDL_SCANCODE_SPACE) {
                SDL_Log("+space");
            }
            if (event.key.keysym.scancode == SDL_SCANCODE_O) {
                SDL_Log("+O");
            }
            if (event.key.keysym.scancode == SDL_SCANCODE_L) {
                SDL_Log("+L");
            }
            if (event.key.keysym.scancode == SDL_SCANCODE_K) {
                SDL_Log("+K");
            }
            if (event.key.keysym.scancode == SDL_SCANCODE_M) {
                SDL_Log("+M");
            }
            break;
        case SDL_KEYUP:
            SDL_Log("-key");
            break;
        case SDL_MOUSEMOTION:
            SDL_Log("mouse (%d %d) (%d %d)", event.motion.x, event.motion.y, event.motion.xrel, event.motion.yrel);
            dx = event.motion.xrel;
            dy = event.motion.yrel;
            break;
        case SDL_MOUSEBUTTONDOWN:
            SDL_Log("+clic (%d %d)", event.button.x, event.button.y);
            x = event.button.x;
            x = event.button.x;
            if (event.button.button == SDL_BUTTON_LEFT) {
                SDL_Log("+left");
            }
            if (event.button.button == SDL_BUTTON_MIDDLE) {
                SDL_Log("+middle");
            }
            if (event.button.button == SDL_BUTTON_RIGHT) {
                SDL_Log("+right");
            }
            break;
        case SDL_MOUSEBUTTONUP:
            SDL_Log("-clic");
            break;
        case SDL_MOUSEWHEEL:
            SDL_Log("molette (%d %d)", event.wheel.x, event.wheel.y);
            break;
        default:
            usleep(ATTENTE);
            continue;
        }

        if (quitter == 1)
            break;

        effacerFenetre();
        synchroniserFenetre();

        ellapsed_time = SDL_GetTicks() - start_time;
        if (ellapsed_time < 1 / 60)
            SDL_Delay(1 / 60 - ellapsed_time);
    }
    fermerFenetre();
}

int main(void)
{
    init();
    touches();
    return 0;
}
