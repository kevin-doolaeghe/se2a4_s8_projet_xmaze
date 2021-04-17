/** Fichiers d'inclusion **/

#include "diffusion.h"

/** Fonctions **/

/**** Diffusion UDP ****/

void tache_diffusion_udp(int* ecoute)
{
    boucle_serveur_udp(*ecoute, (void* (*)(char*, int, char*))reception_diffusion_udp);
}

void reception_diffusion_udp(char* message, int taille, char* ip)
{
#ifdef DEBUG
    printf("udp_diffusion: message of %d bytes from %s: %s\n", taille, ip, message);
#endif

    if (sizeof(message) > sizeof(pr_udp_identite_t)) {
        pr_udp_identite_t* trame = (pr_udp_identite_t*)message;
        server_t tmp;
        init_server(&tmp);

        set_server_id(&tmp, trame->id_serveur);
        set_server_ip(&tmp, ip);
        set_server_port_tcp(&tmp, trame->port_tcp);
        set_server_port_udp_touches(&tmp, trame->port_udp_touches);

        add_server_to_list(&serveur_list, &tmp);

        destroy_server(&tmp);
    }

    if (quitter_client == true)
        exit(EXIT_SUCCESS);
}
