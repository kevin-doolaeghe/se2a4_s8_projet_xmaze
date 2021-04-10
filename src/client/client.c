/** Fichiers d'inclusion **/

#include "client.h"

/** Fonctions **/

void usage() { fprintf(stderr, "Syntaxe : client <ip_serveur>\n"); }

/** ------------------------------------------------- **/

void init_client()
{
    init_sig((void* (*)(void*))detruire_client);

    init_server(&serveur);
    set_server_ip(&serveur, HOST);

    quitter_client = false;
    partie_en_cours = false;

    int chat_sock = init_client_tcp(HOST, PORT_CHAT_TCP);
    creer_tache((void* (*)(void*))tache_ecoute_chat, (void*)&chat_sock, sizeof(chat_sock));

    int diffusion_sock = init_serveur_udp(PORT_DIFFUSION_UDP);
    creer_tache((void* (*)(void*))tache_diffusion_udp, (void*)&diffusion_sock, sizeof(diffusion_sock));

    creer_tache((void* (*)(void*))tache_touches_udp, NULL, 0);

    int graphique_sock = init_serveur_udp(PORT_GRAPHIQUE_UDP);
    creer_tache((void* (*)(void*))tache_gestion_graphique, (void*)&graphique_sock, sizeof(graphique_sock));
}

void detruire_client()
{
    quitter_client = true;
    partie_en_cours = false;

    destroy_server_list(&serveur_list);
    destroy_server(&serveur);

    printf("\nBye !\n");
    usleep(100);
    exit(EXIT_SUCCESS);
}

/** ------------------------------------------------- **/

/**** Chat TCP ****/

void tache_ecoute_chat(int* ecoute)
{
    boucle_reception_tcp(*ecoute, (void* (*)(char*, int))reception_message);
}

void reception_message(char* message, int taille)
{
    printf("tcp_chat: message of %d bytes: %s\n", taille, message);
}

void envoi_message()
{
    while (quitter_client == false) {
        char message[MAX_TAMPON_TCP] = "MESSAGE TCP";
        envoi_message_tcp(serveur.fd, message, MAX_TAMPON_TCP);
        sleep(1);
    }
}

/**** Diffusion UDP ****/

void tache_diffusion_udp(int* ecoute)
{
    boucle_serveur_udp(*ecoute, (void* (*)(char*, int, char*))reception_diffusion_udp);
}

void reception_diffusion_udp(char* message, int taille, char* ip)
{
    printf("udp_diffusion: message of %d bytes from %s: %s\n", taille, ip, message);

    server_t tmp;
    decode_server_from_cstr(&tmp, message);
    add_server_to_list(&serveur_list, &tmp);
    print_server_list(&serveur_list);

    if (quitter_client == true)
        exit(EXIT_SUCCESS);
}

/**** Touches UDP ****/

void tache_touches_udp()
{
    while (quitter_client == false) {
        if (partie_en_cours == false) {
            char message[MAX_TAMPON_UDP] = "TRAME TOUCHE UDP";
            envoi_message_udp(hote, PORT_TOUCHES_UDP, message, MAX_TAMPON_UDP);
        }
        sleep(1);
    }
}

/**** Graphique UDP ****/

void tache_gestion_graphique(int* ecoute)
{
    boucle_serveur_udp(*ecoute, (void* (*)(char*, int, char*))reception_graphique_udp);
}

void reception_graphique_udp(char* message, int taille, char* ip)
{
    printf("udp_graphique: message of %d bytes from %s: %s\n", taille, ip, message);
    if (quitter_client == true)
        exit(EXIT_SUCCESS);
}

/** ------------------------------------------------- **/

/* Fonction principale */

int main(int argc, char* argv[])
{
    // Analyse des arguments
    if (argc != 2) {
        usage();
        exit(EXIT_FAILURE);
    }
    hote = argv[1];

    init_client();

    envoi_message();

    pause();

    return 0;
}
