/** Fichiers d'inclusion **/

#include "graphiques.h"

/** Fonctions **/

/**** Graphiques UDP ****/

void tache_gestion_graphique()
{
    while (quitter_serveur == false) {
        //if (partie_en_cours == true) {
        pt_client_cell_t ptr = client_list;

        while (ptr != NULL) {
            point p = { ptr->client.position.x, ptr->client.position.y, ptr->client.position.z };
            int angle = ptr->client.position.angle;

            mur* m2 = duplique_murs(murs, nb);
            decale_murs(m2, nb, p);
            rotation_murs(m2, nb, angle);
            tri_murs(m2, nb);
            objet2D* objets = malloc(nb * sizeof(objet2D));
            int no;
            projete_murs(m2, nb, objets, &no);

            int taille = sizeof(uint32_t) + no * sizeof(objet2D);

            char* message = malloc(taille);
            int i;
            for (i = 0; i < sizeof(uint32_t); i++)
                message[i] = (no >> (3 - i) * 8) & 0xFF;
            for (i = 0; i < no; i++)
                memcpy(message + sizeof(uint32_t) + i * sizeof(objet2D), &(objets[i]), sizeof(objet2D));

#ifdef DEBUG
            printf("Sending graphic of %d bytes: ", taille);
            for (i = 0; i < taille; i++)
                printf("%02x", message[i]);
            printf("\n");
#endif

            envoi_message_udp(to_cstr(&(ptr->client.ip)), PORT_GRAPHIQUE_UDP, message, taille);

            free(message);
            free(m2);
            free(objets);

            ptr = ptr->next;
        }
        //}
        usleep(ATTENTE_GRAPHIQUE);
    }
}
