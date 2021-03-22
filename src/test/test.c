/** Fichiers d'inclusion **/

#include "test.h"

/** Fonctions **/

void usage()
{
    fprintf(stderr, "Syntax : test <port>\n");
}

void gestion_sig()
{
    running = false;
    printf("\nBye !\n");
    sleep(1);
}

void tache_hello_world()
{
    while (running) {
        printf("Hello World !\n");
        sleep(1);
    }
}

void tache_serveur_tcp(int* s)
{
    creer_tache((void* (*)(void*))gestion_client_tcp, s, sizeof(*s));
}

void gestion_client_tcp(int* s)
{
    char tampon[MAX_TAMPON];
    int ret;

    while ((ret = lire_message_tcp(*s, tampon, MAX_TAMPON - 1)) > 0) {
        if (ret <= 0) {
            detruire_lien_tcp(*s);
            client_count--;
            return;
        }
        tampon[ret] = 0;
        printf("tampon: %s\n", tampon);
    }
}

void tache_serveur_udp(int* s)
{
}

void test_str()
{
    str_t str;
    init_str(&str);

    set_str_from_cstr(&str, "test_str\n");
    print_str(&str);

    destroy_str(&str);
}

void test_str_list()
{
    str_t str;
    init_str(&str);
    str_list_t str_list;
    init_str_list(&str_list);

    set_str_from_cstr(&str, "test_str_list1");
    append_str_to_list(&str_list, &str);
    set_str_from_cstr(&str, "test_str_list2");
    append_str_to_list(&str_list, &str);
    print_str_list(&str_list);

    destroy_str_list(&str_list);
    destroy_str(&str);
}

void test_client()
{
    client_t client;
    init_client(&client);

    print_client(&client);

    destroy_client(&client);
}

void test_client_list()
{
    client_t client;
    init_client(&client);
    client_list_t client_list = NULL;

    append_client_to_list(&client_list, &client);
    append_client_to_list(&client_list, &client);
    append_client_to_list(&client_list, &client);
    print_client_list(&client_list);

    destroy_client_list(&client_list);
    destroy_client(&client);
}

void test_tache()
{
    creer_tache((void* (*)(void*))tache_hello_world, NULL, 0);
}

void test_serveur_tcp(char* service)
{
    int s = init_serveur_tcp(service);
    boucle_serveur_tcp(s, (void* (*)(void*))tache_serveur_tcp);
}

void test_serveur_udp(char* service)
{
    int s = init_serveur_udp(service);

    char tampon[MAX_TAMPON];
    int ret = lire_message_udp(s, tampon, MAX_TAMPON - 1);
    tampon[ret] = 0;
    printf("tampon: %s\n", tampon);
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

    init_sig((void* (*)(void*))gestion_sig);

    //test_str();
    //test_str_list();
    //test_client();
    //test_client_list();
    //test_tache();
    //test_serveur_tcp(service);
    test_serveur_udp(service);

    pause();

    return 0;
}
