/** Fichiers d'inclusion **/

#include "client.h"

/** Fonctions **/

void usage() { fprintf(stderr, "Syntaxe : ./client\n"); }

/** ------------------------------------------------- **/

void init_client()
{
    init_sig((void* (*)(void*))detruire_client);

    init_server(&serveur);

    unsigned char resultat = creerFenetre(LARGEUR, HAUTEUR, TITRE);
    if (!resultat) {
        fprintf(stderr, "Problème graphique !\n");
        exit(EXIT_FAILURE);
    }

    effacerFenetre();
    synchroniserFenetre();

    quitter_client = false;
    partie_en_cours = false;

    int diffusion_sock = init_serveur_udp(PORT_DIFFUSION_UDP);
    creer_tache((void* (*)(void*))tache_diffusion_udp, (void*)&diffusion_sock, sizeof(diffusion_sock));
}

void detruire_client()
{
    quitter_client = true;
    partie_en_cours = false;

    fermerFenetre();

    destroy_server_list(&serveur_list);
    destroy_server(&serveur);

    printf("\nBye !\n");
    usleep(ATTENTE);
    exit(EXIT_SUCCESS);
}

/** ------------------------------------------------- **/

/**** Chat TCP ****/

void connexion_chat(int id)
{
    if (size_of_server_list(&serveur_list) >= id && serveur.fd == -1) {
        pt_server_cell_t tmp = serveur_list;
        int current = 1;
        while (current != id)
            tmp = tmp->next;
        copy_server(&serveur, &(tmp->server));

        int chat_sock = init_client_tcp(to_cstr(&(serveur.ip)), PORT_CHAT_TCP);
        set_server_fd(&serveur, chat_sock);
        creer_tache((void* (*)(void*))tache_ecoute_chat, (void*)&chat_sock, sizeof(chat_sock));

        int graphique_sock = init_serveur_udp(PORT_GRAPHIQUE_UDP);
        creer_tache((void* (*)(void*))tache_gestion_graphique, (void*)&graphique_sock, sizeof(graphique_sock));

        creer_tache((void* (*)(void*))gestion_evenements, NULL, 0);
    }
}

void tache_ecoute_chat(int* ecoute)
{
    boucle_reception_tcp(*ecoute, (void* (*)(char*, int))reception_message_chat);
}

void reception_message_chat(char* message, int taille)
{
    printf("tcp_chat: message of %d bytes: %s\n", taille, message);
}

void envoi_message_chat(char* message)
{
    if (serveur.fd != -1)
        envoi_message_tcp(serveur.fd, message, strlen(message));
}

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

        if (touche != 0 && touche != TOUCHE_AUTRE) {
#ifdef DEBUG
            printf("touche: %08x\n", touche);
#endif
            tache_touches_udp(touche);
        }
    }
}

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
    trame.objets = (objet2D*)&(message[sizeof(trame.nb_objets)]);

#ifdef DEBUG
    printf("udp_graphique: message of %d bytes from %s.\n", taille, ip);
    printf("%d objets graphiques reçus:\n", trame.nb_objets);
    for (i = 0; i < taille; i++)
        printf("%02x", message[i]);
    printf("\n");
#endif

    effacerFenetre();
    dessine_2D(trame.objets, trame.nb_objets);
    synchroniserFenetre();

    if (quitter_client == true)
        exit(EXIT_SUCCESS);
}

/** ------------------------------------------------- **/

void boucle_commande()
{
    while (quitter_client != true) {
        char* commande;
        size_t taille = 0;

        printf("> ");
        getline(&commande, &taille, stdin);
        commande[strlen(commande) - 1] = '\0';

        str_list_t tokens;
        init_str_list(&tokens);
        split_cstr_to_str_list(&tokens, " ", commande);

        if (!strcmp(to_cstr(&(tokens.str_list[0])), "help")) {
            printf("Liste des commandes :\n");
            printf("\t\t- help: Affiche l'aide\n");
            printf("\t\t- list: Affiche les serveurs trouvés\n");
            printf("\t\t- connect: Se connecte au premier serveur de la liste\n");
            printf("\t\t- send: Envoi un message\n");
        } else if (!strcmp(to_cstr(&(tokens.str_list[0])), "list")) {
            print_server_list(&serveur_list);
        } else if (!strcmp(to_cstr(&(tokens.str_list[0])), "connect") && tokens.alloc == 2) {
            int id = atoi(to_cstr(&(tokens.str_list[1])));
            connexion_chat(id);
        } else if (!strcmp(to_cstr(&(tokens.str_list[0])), "send") && tokens.alloc > 1) {
            char message[MAX_TAMPON_TCP];
            int i;

            strcpy(message, "");
            for (i = 1; i < tokens.alloc; i++) {
                strcat(message, to_cstr(&(tokens.str_list[i])));
                strcat(message, " ");
            }
            strcat(message, "\0");

            envoi_message_chat(message);
        } else {
            printf("Commande non reconnue..\n");
        }

        destroy_str_list(&tokens);
        free(commande);
    }
}

/** ------------------------------------------------- **/

/* Fonction principale */

int main(int argc, char* argv[])
{
    // Analyse des arguments
    if (argc != 1) {
        usage();
        exit(EXIT_FAILURE);
    }

    init_client();

    boucle_commande();

    pause();

    return 0;
}
