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
    printf("\t\t- help: Affiche l'aide\n");
    printf("\t\t- list: Affiche les serveurs trouvés\n");
    printf("\t\t- connect <id>: Se connecte au premier serveur de la liste\n");
    printf("\t\t- send <msg>: Envoi un message\n");
    printf("\t\t- id: Affiche l'identifiant du client\n");
    printf("\t\t- nick <nickname>: Change le pseudo\n");
    printf("\t\t- start: Démarre la partie\n");
    printf("\t\t- stop: Arrête la partie\n");
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
        pr_tcp_chat_t trame;
        trame.id_client = id;
        trame.commande = commande;
        trame.message = NULL;

        char message[MAX_TAMPON_TCP];
        memcpy(message, &trame, sizeof(pr_tcp_chat_t));

        char tmp[MAX_TAMPON_TCP - sizeof(pr_tcp_chat_t)];
        strcpy(tmp, "");
        int taille = sizeof(trame.id_client) + sizeof(trame.commande);
        int i;

        switch (commande) {
        case CMD_MESG_ID:
            for (i = 1; i < tokens->alloc; i++) {
                strcat(tmp, to_cstr(&(tokens->str_list[i])));
                if (i != tokens->alloc - 1)
                    strcat(tmp, " ");
            }
            strcat(tmp, "\0");
            break;
        case CMD_NICK_ID:
            strcat(tmp, to_cstr(&(tokens->str_list[1])));
            strcat(tmp, "\0");
            break;
        case CMD_STRT_ID:
            break;
        case CMD_STOP_ID:
            break;
        default:
            break;
        }
        memcpy(message + taille, tmp, strlen(tmp));
        taille += strlen(tmp);

#ifdef DEBUG
        printf("Sending message of %d bytes: ", taille);
        for (i = 0; i < taille; i++)
            printf("%2.2x", message[i]);
        printf("\n");
#endif

        envoi_message_tcp(serveur.fd, message, taille);
    }
}