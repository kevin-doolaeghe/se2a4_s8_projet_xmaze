/** Fichiers d'inclusion **/

#include "client.h"

/** Fonctions **/

void usage() { fprintf(stderr, "Syntaxe : ./client\n"); }

void init_client()
{
    // Initialisation des signaux
    init_sig((void* (*)(void*))detruire_client);

    // Initialisation des variables
    init_server(&serveur);

    quitter_client = false;
    connecte_au_serveur = false;
    partie_en_cours = false;

    id = -1;

    // Demarrage de la tache de detection des serveurs
    int diffusion_sock = init_serveur_udp(PORT_DIFFUSION_UDP);
    create_task((void* (*)(void*))thread_diffusion, (void*)&diffusion_sock, sizeof(diffusion_sock));
}

void detruire_client()
{
    // Deconnexion du serveur (arret implicite de la partie)
    if (connecte_au_serveur == true)
        deconnexion_serveur();

    // Arret du client
    quitter_client = true;

    // Nettoyage
    destroy_server_list(&serveur_list);
    destroy_server(&serveur);

    // Delai d'attente
    printf("\nBye !\n");
    usleep(ATTENTE);
    exit(EXIT_SUCCESS);
}

void connexion_serveur(int id)
{
    // Recuperation du serveur
    server_t* res = get_server_by_id(&serveur_list, id);
    copy_server(&serveur, res);

    // Recuperation du port
    char port[MAX_PORT_LEN];
    sprintf(port, "%d", serveur.port_tcp);

    // Connecte au serveur
    connecte_au_serveur = true;

    // Demarrage de la tache de dialogue
    int chat_sock = init_client_tcp(to_cstr(&(serveur.ip)), port);
    set_server_fd(&serveur, chat_sock);
    create_task((void* (*)(void*))thread_chat, (void*)&chat_sock, sizeof(chat_sock));
}

void deconnexion_serveur()
{
    // Arret de la partie
    if (partie_en_cours == true)
        arreter_partie();

    // Non connecte au serveur
    connecte_au_serveur = false;

    // Deconnexion du serveur
    detruire_lien_tcp(serveur.fd);

    // Reinitialisation du serveur
    destroy_server(&serveur);
    init_server(&serveur);

    id = -1;
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
