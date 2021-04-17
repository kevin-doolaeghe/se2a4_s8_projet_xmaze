/** Fichiers d'inclusion **/

#include "chat.h"

/** Fonctions **/

/**** Chat TCP ****/

void tache_gestion_chat(int* dialogue)
{
    boucle_serveur_tcp(*dialogue, (void* (*)(int, char*))gestion_client);
}

void gestion_client(int dialogue, char* ip)
{
#ifdef DEBUG
    printf("Recieved TCP connection demmand from %s\n", ip);
#endif

    //char tampon[MAX_TAMPON_TCP];
    //int ret;

    client_t client;
    init_client(&client);

    /*
    ret = lire_message_tcp(dialogue, tampon, MAX_TAMPON_TCP);
    if (ret <= 0)
        return;
    */

    set_client_fd(&client, dialogue);
    set_client_ip(&client, ip);
    set_client_pseudo(&client, "pseudotest");
    pos_t pos = { LABY_X / 2 * MUR_TAILLE, 0, MUR_TAILLE, 0 };
    set_client_position(&client, &pos);

    append_client_to_list(&client_list, &client);
    print_client_list(&client_list);

    create_task((void* (*)(void*))tache_discussion_client, (void*)&dialogue, sizeof(dialogue));

    destroy_client(&client);
}

void tache_discussion_client(int* dialogue)
{
    boucle_reception_tcp(*dialogue, (void* (*)(char*, int))reception_message);

    delete_client_from_list(&client_list, *dialogue);
    print_client_list(&client_list);
}

void reception_message(char* message, int taille)
{
    printf("chat_tcp: message of %d bytes: %s\n", taille, message);

    pt_client_cell_t ptr = client_list;

    while (ptr != NULL) {
        envoi_message_tcp(ptr->client.fd, message, taille);
        ptr = ptr->next;
    }
}
