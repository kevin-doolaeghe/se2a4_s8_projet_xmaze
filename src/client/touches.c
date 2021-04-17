/** Fichiers d'inclusion **/

#include "touches.h"

/** Fonctions **/

/**** Touches UDP ****/

void tache_touches_udp(int touche)
{
    pr_udp_touches_t trame;
    trame.id_client = id;
    trame.touches = touche;

    char message[sizeof(pr_udp_touches_t)];
    memcpy(message, &trame, sizeof(pr_udp_touches_t));

    envoi_message_udp(to_cstr(&(serveur.ip)), PORT_TOUCHES_UDP, message, sizeof(pr_udp_touches_t));
}

void gestion_evenements()
{
    int touche;
    unsigned char fenetre, quitter;
    while (1) {
        int evenement = attendreEvenement(&touche, &fenetre, &quitter);
        if (!evenement) {
            usleep(ATTENTE);
            continue;
        }

        if (quitter == 1)
            detruire_client();

        if (touche != 0 && touche != TOUCHE_AUTRE && serveur.fd != -1) {
#ifdef DEBUG
            printf("touche: %08x\n", touche);
#endif
            tache_touches_udp(touche);
        }
    }
}