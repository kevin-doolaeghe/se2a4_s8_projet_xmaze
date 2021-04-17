/** Fichiers d'inclusion **/

#include "interaction.h"

/** Variables **/

str_list_t tokens;

/** Fonctions **/

void boucle_saisie_commande()
{
    int commande;
    init_str_list(&tokens);

    while (quitter_client != true) {
        printf("> ");

        lire_ligne(&tokens);

        if (!strcmp(to_cstr(&(tokens.str_list[0])), CMD_HELP)) {
            commande = ID_HELP;
        } else if (!strcmp(to_cstr(&(tokens.str_list[0])), CMD_LIST)) {
            commande = ID_LIST;
        } else if (!strcmp(to_cstr(&(tokens.str_list[0])), CMD_CONN) && tokens.alloc == 2) {
            commande = ID_CONN;
        } else if (!strcmp(to_cstr(&(tokens.str_list[0])), CMD_MESG) && tokens.alloc > 1) {
            commande = ID_MESG;
        } else {
        }

        traitement_commande(commande);
    }
    destroy_str_list(&tokens);
}

void traitement_commande(int commande)
{
    switch (commande) {
    case ID_HELP:
        afficher_aide();
        break;
    case ID_LIST:
        print_server_list(&serveur_list);
        break;
    case ID_CONN:
        connexion_chat(atoi(to_cstr(&(tokens.str_list[1]))));
        break;
    case ID_MESG:
        envoyer_message();
        break;
    default:
        break;
    }
}

void lire_ligne(str_list_t* tokens)
{
    char* commande;
    size_t taille = 0;

    getline(&commande, &taille, stdin);
    commande[strlen(commande) - 1] = '\0';

    split_cstr_to_str_list(tokens, " ", commande);

    free(commande);
}

void afficher_aide()
{
    printf("Liste des commandes :\n");
    printf("\t\t- help\t\t\t: Affiche l'aide\n");
    printf("\t\t- list\t\t\t: Affiche les serveurs trouvés\n");
    printf("\t\t- connect <id>\t: Se connecte au premier serveur de la liste\n");
    printf("\t\t- send <msg>\t\t: Envoi un message\n");
}

void afficher_erreur()
{
    printf("Commande non reconnue..\n");
}

void envoyer_message()
{
    char message[MAX_TAMPON_TCP];
    int i;

    strcpy(message, "");
    for (i = 1; i < tokens.alloc; i++) {
        strcat(message, to_cstr(&(tokens.str_list[i])));
        strcat(message, " ");
    }
    strcat(message, "\0");

    if (serveur.fd != -1)
        envoi_message_tcp(serveur.fd, message, strlen(message));
}