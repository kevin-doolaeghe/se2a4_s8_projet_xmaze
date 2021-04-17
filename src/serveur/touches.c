/** Fichiers d'inclusion **/

#include "touches.h"

/** Fonctions **/

/**** Touches UDP ****/

void tache_gestion_touches(int* ecoute)
{
    boucle_serveur_udp(*ecoute, (void* (*)(char*, int, char*))reception_touches_udp);
}

void reception_touches_udp(char* message, int taille, char* ip)
{
#ifdef DEBUG
    printf("udp_touches: message of %d bytes from %s: ", taille, ip);
    int i;
    for (i = 0; i < sizeof(message); i++)
        printf("%08x", message[i]);
    printf("\n");
#endif

    pr_udp_touches_t* trame = (pr_udp_touches_t*)message;

    int touche = trame->touches;
    printf("touche: %d\n", touche);
    client_t* client = get_client_by_id(&client_list, trame->id_client);

    if (touche == TOUCHE_DROITE)
        client->position.angle += 10;
    if (touche == TOUCHE_GAUCHE)
        client->position.angle -= 10;
    if (client->position.angle < 0 || client->position.angle > 360)
        client->position.angle = client->position.angle % 360;
    if (touche == TOUCHE_HAUT) {
        client->position.x += MUR_TAILLE / 10 * sin(2 * M_PI * client->position.angle / 360);
        client->position.z += MUR_TAILLE / 10 * cos(2 * M_PI * client->position.angle / 360);
    }
    if (touche == TOUCHE_BAS) {
        client->position.x -= MUR_TAILLE / 10 * sin(2 * M_PI * client->position.angle / 360);
        client->position.z -= MUR_TAILLE / 10 * cos(2 * M_PI * client->position.angle / 360);
    }

    if (quitter_serveur == true)
        exit(EXIT_SUCCESS);
}
