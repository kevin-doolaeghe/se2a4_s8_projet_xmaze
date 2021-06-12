/** Fichiers d'inclusion **/

#include "client.h"

/** Fonctions **/

void usage() { fprintf(stderr, "Syntaxe : ./client\n"); }

void init_client()
{
    printf("Démarrage du client..\n");
    afficher_aide();

    // Initialisation des signaux
    init_sig((void* (*)(void*))detruire_client);
    init_mutex_list();

    // Initialisation des variables
    p(MUTEX_SERV);
    init_server(&serveur);
    v(MUTEX_SERV);

    p(MUTEX_QUIT);
    quitter_client = false;
    v(MUTEX_QUIT);
    p(MUTEX_CONN);
    connecte_au_serveur = false;
    v(MUTEX_CONN);
    p(MUTEX_PLAY);
    partie_en_cours = false;
    v(MUTEX_PLAY);

    p(MUTEX_IDTF);
    id = -1;
    v(MUTEX_IDTF);

    // Demarrage de la tache de detection des serveurs
    int diffusion_sock = init_serveur_udp(PORT_DIFFUSION_UDP);
    create_task((void* (*)(void*))thread_diffusion, (void*)&diffusion_sock, sizeof(diffusion_sock));
}

void detruire_client()
{
    printf("\n\nBye !\n");

    // Deconnexion du serveur (arret implicite de la partie)
    if (connecte_au_serveur == true)
        deconnexion_serveur();

    // Arret du client
    p(MUTEX_QUIT);
    quitter_client = true;
    v(MUTEX_QUIT);

    // Nettoyage
    p(MUTEX_LIST);
    destroy_server_list(&liste_serveur);
    v(MUTEX_LIST);
    p(MUTEX_SERV);
    destroy_server(&serveur);
    v(MUTEX_SERV);

    // Delai d'attente
    usleep(ATTENTE);
    exit(EXIT_SUCCESS);
}

void connexion_serveur(int id)
{
    printf("\nConnexion au serveur %d.\n", id);

    // Recuperation du serveur
    p(MUTEX_LIST);
    server_t* res = get_server_by_id(&liste_serveur, id);
    copy_server(&serveur, res);
    v(MUTEX_LIST);

    // Recuperation du port
    char port[MAX_PORT_LEN];
    sprintf(port, "%d", serveur.port_tcp);

    // Connecte au serveur
    p(MUTEX_CONN);
    connecte_au_serveur = true;
    v(MUTEX_CONN);

    // Demarrage de la tache de dialogue
    int chat_sock = init_client_tcp(to_cstr(&(serveur.ip)), port);
    set_server_fd(&serveur, chat_sock);
    create_task((void* (*)(void*))thread_chat, (void*)&chat_sock, sizeof(chat_sock));
}

void deconnexion_serveur()
{
    printf("\nDéconnexion du serveur..\n");

    // Non connecte au serveur
    p(MUTEX_CONN);
    connecte_au_serveur = false;
    v(MUTEX_CONN);

    // Deconnexion du serveur
    detruire_lien_tcp(serveur.fd);

    // Reinitialisation du serveur
    p(MUTEX_SERV);
    destroy_server(&serveur);
    init_server(&serveur);
    v(MUTEX_SERV);

    p(MUTEX_IDTF);
    id = -1;
    v(MUTEX_IDTF);

    // Arret du jeu
    if (partie_en_cours == true)
        arreter_jeu();
}

void demarrer_jeu()
{
    printf("\nDémarrage du jeu!\n");

    // Demarrage de la partie
    p(MUTEX_PLAY);
    partie_en_cours = true;
    v(MUTEX_PLAY);

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

void arreter_jeu()
{
    printf("\nArrêt du jeu.\n");

    // Arret de la partie
    p(MUTEX_PLAY);
    partie_en_cours = false;
    v(MUTEX_PLAY);

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
