/** Fichiers d'inclusion **/

#include "interaction.h"

/** Fonctions **/

void boucle_saisie_commande()
{
    str_list_t tokens;
    int commande;
    init_str_list(&tokens);

    while (quitter_client != true) {
        printf("> ");

        lire_ligne(&tokens);

        if (!strcmp(to_cstr(&(tokens.str_list[0])), CMD_HELP_STR) && tokens.alloc == 1) {
            commande = CMD_HELP_ID;
        } else if (!strcmp(to_cstr(&(tokens.str_list[0])), CMD_LIST_STR) && tokens.alloc == 1) {
            commande = CMD_LIST_ID;
        } else if (!strcmp(to_cstr(&(tokens.str_list[0])), CMD_CONN_STR) && tokens.alloc == 2) {
            commande = CMD_CONN_ID;
        } else if (!strcmp(to_cstr(&(tokens.str_list[0])), CMD_MESG_STR) && tokens.alloc > 1) {
            commande = CMD_MESG_ID;
        } else if (!strcmp(to_cstr(&(tokens.str_list[0])), CMD_IDTF_STR) && tokens.alloc == 1) {
            commande = CMD_IDTF_ID;
        } else if (!strcmp(to_cstr(&(tokens.str_list[0])), CMD_NICK_STR) && tokens.alloc == 2) {
            commande = CMD_NICK_ID;
        } else if (!strcmp(to_cstr(&(tokens.str_list[0])), CMD_STRT_STR) && tokens.alloc == 1) {
            commande = CMD_STRT_ID;
        } else if (!strcmp(to_cstr(&(tokens.str_list[0])), CMD_STOP_STR) && tokens.alloc == 1) {
            commande = CMD_STOP_ID;
        } else if (!strcmp(to_cstr(&(tokens.str_list[0])), CMD_EMPT_STR)) {
            commande = CMD_EMPT_ID;
        } else {
            commande = CMD_OTHR_ID;
        }

        traitement_commande(commande, &tokens);
    }
    destroy_str_list(&tokens);
}

void traitement_commande(int commande, str_list_t* tokens)
{
    switch (commande) {
    case CMD_HELP_ID:
        afficher_aide();
        break;
    case CMD_LIST_ID:
        print_server_list(&serveur_list);
        break;
    case CMD_CONN_ID:
        connexion_chat(atoi(to_cstr(&(tokens->str_list[1]))));
        break;
    case CMD_MESG_ID:
        envoi_message(commande, tokens);
        break;
    case CMD_IDTF_ID:
        printf("id: %d\n", id);
        break;
    case CMD_NICK_ID:
        if (serveur.fd != -1) {
            envoi_message(commande, tokens);
        }
        break;
    case CMD_STRT_ID:
        if (serveur.fd != -1) {
            if (id == 0)
                envoi_message(commande, tokens);
            else
                afficher_erreur_admin();
        }
        break;
    case CMD_STOP_ID:
        if (serveur.fd != -1) {
            if (id == 0)
                envoi_message(commande, tokens);
            else
                afficher_erreur_admin();
        }
        break;
    case CMD_OTHR_ID:
        afficher_erreur_saisie();
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
    printf("\t- help: Affiche l'aide\n");
    printf("\t- list: Affiche les serveurs trouvés\n");
    printf("\t- connect <id>: Se connecte au premier serveur de la liste\n");
    printf("\t- send <msg>: Envoi un message\n");
    printf("\t- id: Affiche l'identifiant du client\n");
    printf("\t- nick <nickname>: Change le pseudo\n");
    printf("\t- start: Démarre la partie\n");
    printf("\t- stop: Arrête la partie\n");
}

void afficher_erreur_saisie()
{
    printf("Commande non reconnue\n");
}

void afficher_erreur_admin()
{
    printf("Vous n'êtes pas administrateur\n");
}

void envoi_message(int commande, str_list_t* tokens)
{
    if (serveur.fd != -1) {
        // Fabrication du message a envoyer
        char str[MAX_MESG_LEN];
        int i;
        switch (commande) {
        case CMD_MESG_ID:
            for (i = 1; i < tokens->alloc; i++) {
                strcat(str, to_cstr(&(tokens->str_list[i])));
                if (i != tokens->alloc - 1)
                    strcat(str, " ");
            }
            strcat(str, "\0");
            break;
        case CMD_NICK_ID:
            strcat(str, to_cstr(&(tokens->str_list[1])));
            strcat(str, "\0");
            break;
        default:
            break;
        }
        printf("Message: %s\n", str);

        // Preparation de la trame
        pr_tcp_chat_t trame;
        trame.id_client = id;
        trame.commande = commande;
        trame.message = str;

        int taille = sizeof(trame.id_client) + sizeof(trame.commande) + strlen(str);
        char message[taille];

        // Ecriture de la trame
        ecrire_trame_chat(&trame, message, taille);

        // Envoi de la trame
        envoi_message_tcp(serveur.fd, message, taille);

#ifdef DEBUG
        printf("Sending message of %d bytes: ", taille);
        for (i = 0; i < taille; i++)
            printf("%02x", message[i]);
        printf("\n");
#endif
    }
}