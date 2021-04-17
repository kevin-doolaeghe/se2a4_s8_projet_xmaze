/** Fichiers d'inclusion **/

#include "graphiques.h"

/** Fonctions **/

/**** Graphique UDP ****/

void tache_gestion_graphique(int* ecoute)
{
    boucle_serveur_udp(*ecoute, (void* (*)(char*, int, char*))reception_graphique_udp);
}

void reception_graphique_udp(char* message, int taille, char* ip)
{
    pr_udp_graph_t trame;
    trame.nb_objets = 0;
    int i;
    for (i = 0; i < sizeof(trame.nb_objets); i++)
        trame.nb_objets += message[3 - i] << (i * 8);
    trame.objets = (objet_2d_t*)&(message[sizeof(trame.nb_objets)]);

#ifdef DEBUG
    printf("udp_graphique: message of %d bytes from %s.\n", taille, ip);
    printf("%d objets graphiques reçus:\n", trame.nb_objets);
    for (i = 0; i < taille; i++)
        printf("%02x", message[i]);
    printf("\n");
#endif

    effacerFenetre();
    dessine_2D((objet2D*)trame.objets, trame.nb_objets);
    synchroniserFenetre();

    if (quitter_client == true)
        exit(EXIT_SUCCESS);
}
