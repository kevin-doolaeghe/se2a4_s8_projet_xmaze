/** Fichiers d'inclusion **/

#include "chat.h"

/** Fonctions **/

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
        create_task((void* (*)(void*))tache_ecoute_chat, (void*)&chat_sock, sizeof(chat_sock));

        int graphique_sock = init_serveur_udp(PORT_GRAPHIQUE_UDP);
        create_task((void* (*)(void*))tache_gestion_graphique, (void*)&graphique_sock, sizeof(graphique_sock));
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
