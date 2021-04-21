/** Fichiers d'inclusion **/

#include "client.h"

/** Fonctions **/

void usage() { fprintf(stderr, "Syntaxe : ./client\n"); }

void init_client()
{
    init_sig((void* (*)(void*))detruire_client);

    init_server(&serveur);

    quitter_client = false;
    partie_en_cours = false;

    id = -1;

    int diffusion_sock = init_serveur_udp(PORT_DIFFUSION_UDP);
    create_task((void* (*)(void*))thread_diffusion, (void*)&diffusion_sock, sizeof(diffusion_sock));
}

void detruire_client()
{
    quitter_client = true;
    partie_en_cours = false;

    destroy_server_list(&serveur_list);
    destroy_server(&serveur);

    printf("\nBye !\n");
    usleep(ATTENTE);
    exit(EXIT_SUCCESS);
}

void demarrer_partie()
{
    // Demarrage de la partie
    partie_en_cours = true;

    // Ouverture de la fenetre
    unsigned char resultat = creerFenetre(LARGEUR, HAUTEUR, TITRE);
    if (!resultat) {
        fprintf(stderr, "Problème graphique !\n");
        exit(EXIT_FAILURE);
    }

    // Demarrage de la tache d'envoi des touches
    create_task((void* (*)(void*))thread_touches, NULL, 0);

    // Demarrage de la tache de reception des objets graphiques
    int graphique_sock = init_serveur_udp(PORT_GRAPHIQUE_UDP);
    create_task((void* (*)(void*))thread_graphique, (void*)&graphique_sock, sizeof(graphique_sock));
}

void arreter_partie()
{
    // Arret de la partie
    partie_en_cours = false;

    usleep(ATTENTE);

    // Fermeture de la fenetre
    fermerFenetre();
}

void connexion_serveur(int id)
{
    if (search_server_in_list(&serveur_list, id) && serveur.fd == -1) {
        // Recuperation du serveur
        server_t* res = get_server_by_id(&serveur_list, id);
        copy_server(&serveur, res);

        // Recuperation du port
        char port[MAX_PORT_LEN];
        sprintf(port, "%d", serveur.port_tcp);

        // Demarrage de la tache de dialogue
        int chat_sock = init_client_tcp(to_cstr(&(serveur.ip)), port);
        set_server_fd(&serveur, chat_sock);
        create_task((void* (*)(void*))thread_chat, (void*)&chat_sock, sizeof(chat_sock));
    }
}

void deconnexion_serveur()
{
}

/* Fonction principale */

int main(int argc, char* argv[])
{
    // Analyse des arguments
    if (argc != 1) {
        usage();
        exit(EXIT_FAILURE);
    }

    init_client();
    boucle_saisie_commande();

    pause();
    return 0;
}
