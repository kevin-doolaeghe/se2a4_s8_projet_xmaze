/** Fichiers d'inclusion **/

#include "shell.h"

/** Fonctions **/

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
