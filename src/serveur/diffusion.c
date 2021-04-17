/** Fichiers d'inclusion **/

#include "diffusion.h"

/** Fonctions **/

/**** Diffusion UDP ****/

void tache_diffusion_udp()
{
    while (quitter_serveur == false) {
        if (partie_en_cours == false) {
            pr_udp_identite_t trame;
            trame.id_serveur = ID_SERVEUR;
            trame.port_tcp = atoi(PORT_CHAT_TCP);
            trame.port_udp_touches = atoi(PORT_TOUCHES_UDP);

            char message[sizeof(pr_udp_identite_t)];
            memcpy(message, &trame, sizeof(pr_udp_identite_t));

            envoi_message_udp(BROADCAST, PORT_DIFFUSION_UDP, message, sizeof(pr_udp_identite_t));
        }
        sleep(3);
    }
}
