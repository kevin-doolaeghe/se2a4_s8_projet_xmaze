/** Fichiers d'inclusion **/

#include "test.h"

/** Fonctions **/

void usage()
{
    fprintf(stderr, "Syntax : test <port>\n");
}

void hello_world()
{
    while (1) {
        printf("Hello World !\n");
        sleep(1);
    }
}

/* Fonction principale */

int main(int argc, char* argv[])
{
    // Analyse des arguments
    if (argc != 2) {
        usage();
        exit(-1);
    }
    char* service = argv[1];

    init_sig();

    str_t str;
    init_str(&str);
    set_str_from_cstr(&str, "Hello!\n");
    print_str(&str);
    str_list_t str_list;
    init_str_list(&str_list);
    append_str_to_list(&str_list, &str);
    set_str_from_cstr(&str, "Hello2!\n");
    append_str_to_list(&str_list, &str);
    print_str_list(&str_list);

    client_t client;
    init_client(&client);
    pos_t pos;
    init_pos(&pos);
    set_client(&client, 1, "Kevin", &pos);
    copy_str_list(&(client.message_list), &str_list);
    print_client(&client);

    client_list_t client_list = NULL;
    append_client_to_list(&client_list, &client);
    print_client_list(&client_list);
    destroy_client_list(&client_list);
    destroy_client(&client);

    destroy_str(&str);
    destroy_str_list(&str_list);

    creer_tache((void* (*)(void*))hello_world, NULL, 0);

    pause();

    return 0;
}
