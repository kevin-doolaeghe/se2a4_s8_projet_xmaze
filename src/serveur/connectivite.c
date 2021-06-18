/** Fichiers d'inclusion **/

#include "connectivite.h"

/** Variables **/

objet3D murs[(LABY_X + 1) * LABY_Y + (LABY_Y + 1) * LABY_X];

int nb_murs;

char* laby[2 * LABY_Y + 1] = {
    " - - - - - - - - ",
    "|. . . . . . . .|",
    "                 ",
    "|. .|. . . . . .|",
    "       - -       ",
    "|. .|.|. .|. . .|",
    "                 ",
    "|. .|.|. .|. . .|",
    "                 ",
    "|. .|.|. .|. . .|",
    "       - -       ",
    "|. .|.|. . . . .|",
    "                 ",
    "|. .|.|. . . . .|",
    "                 ",
    "|. . . . . . . .|",
    " - - - - - - - - "
};

/** Fonctions **/

/**** Taches ****/

void thread_chat_connexion(int* dialogue)
{
    boucle_serveur_tcp(*dialogue, (void* (*)(int, char*))connexion_client);
}

void thread_chat_dialogue(int* dialogue)
{
    boucle_reception_tcp(*dialogue, (void* (*)(char*, int))reception_message);
    deconnexion_client(*dialogue);
}

void thread_diffusion()
{
    diffuser_identite();
}

void thread_actualisation_jeu()
{
    boucle_actualisation_jeu();
}

void thread_touches(int* ecoute)
{
    boucle_serveur_udp(*ecoute, (void* (*)(char*, int, char*))reception_touche);
}

void thread_graphique()
{
    calcul_graphique();
}

/**** Chat TCP ****/

void connexion_client(int dialogue, char* ip)
{
#ifdef DEBUG
    printf("Etablished TCP connection with %s\n", ip);
#endif

    // Ajout du client a la liste
    client_t client;
    init_client(&client);

    set_client_fd(&client, dialogue);
    set_client_ip(&client, ip);
    pos_t pos = { 0, 0, 0, 0 };
    set_client_position(&client, &pos);

    p(MUTEX_LIST);
    append_client_to_list(&client_list, &client);
    order_list(&client_list);

    printf("Liste des clients:\n");
    print_client_list(&client_list);
    v(MUTEX_LIST);

    // Demarrage de la tache de dialogue
    create_task((void* (*)(void*))thread_chat_dialogue, (void*)&dialogue, sizeof(dialogue));
    envoi_trame_chat(dialogue, size_of_client_list(&client_list) - 1, CMD_IDTF_ID);

    destroy_client(&client);
}

void deconnexion_client(int dialogue)
{
    p(MUTEX_LIST);
    client_t* client = get_client_by_fd(&client_list, dialogue);
    int id = client->id;
#ifdef DEBUG
    printf("Client with id %d disconnected\n", id);
#endif

    delete_client_from_list(&client_list, dialogue);

    if (id == ID_ADMIN && partie_en_cours == true)
        arreter_partie();

    order_list(&client_list);

    printf("Liste des clients:\n");
    print_client_list(&client_list);

    pt_client_cell_t ptr = client_list;
    while (ptr != NULL) {
        envoi_trame_chat(ptr->client.fd, ptr->client.id, CMD_IDTF_ID);
        ptr = ptr->next;
    }
    v(MUTEX_LIST);
}

void reception_message(char* message, int taille)
{
    // Traduction de la trame
    pr_tcp_chat_t trame;
    traduire_trame_chat(&trame, message, taille);

#ifdef DEBUG
    printf("Recieved message of %d bytes.\n", taille);
    printf("\t- ID: %d\n\t- Command: %d\n\t- Content: %s\n", trame.id_client, trame.commande, trame.message);
#endif

    p(MUTEX_LIST);
    client_t* client = get_client_by_id(&client_list, trame.id_client);
    if (client != NULL) {
        // Traitement du message recu
        if (trame.commande == CMD_MESG_ID) {
            // Fabrication du message a envoyer
            char str[MAX_TAMPON_TCP];
            strcpy(str, "");

            time_t rawtime;
            struct tm* timeinfo;
            time(&rawtime);
            timeinfo = localtime(&rawtime);
            strcat(str, asctime(timeinfo));
            str[strlen(str) - 1] = '\0';

            strcat(str, " | ");
            if (strlen(to_cstr(&(client->pseudo))) != 0)
                strcat(str, to_cstr(&(client->pseudo)));
            else
                strcat(str, "Anonymous");
            strcat(str, " wrote: ");
            strcat(str, trame.message);
            trame.message = str;

            // Diffusion du message
            diffuser_message_chat(&trame);
        } else if (trame.commande == CMD_NICK_ID) {
            set_client_pseudo(client, trame.message);
            print_client_list(&client_list);
        } else if (trame.commande == CMD_STRT_ID) {
            demarrer_partie();
        } else if (trame.commande == CMD_STOP_ID) {
            arreter_partie();
        } else if (trame.commande == CMD_DISC_ID) {
            // Fabrication du message a envoyer
            char str[MAX_TAMPON_TCP];
            strcpy(str, "");
            if (strlen(to_cstr(&(client->pseudo))) != 0)
                strcat(str, to_cstr(&(client->pseudo)));
            else
                strcat(str, "Anonymous");
            strcat(str, " disconnected.");
            trame.message = str;

            // Diffusion du message
            diffuser_message_chat(&trame);
        }
    }
    v(MUTEX_LIST);
}

void envoi_trame_chat(int dialogue, int id, int commande)
{
    // Preparation de la trame
    pr_tcp_chat_t trame;
    trame.id_client = id;
    trame.commande = commande;
    trame.message = NULL;

    int taille = sizeof(trame.id_client) + sizeof(trame.commande);
    char message[taille];

    // Ecriture de la trame
    ecrire_trame_chat(&trame, message, taille);

    // Envoi de la trame
    envoi_message_tcp(dialogue, message, taille);
}

void diffuser_message_chat(pr_tcp_chat_t* trame)
{
    // Preparation de la trame
    int taille = sizeof(trame->id_client) + sizeof(trame->commande) + strlen(trame->message);
    char reponse[taille];

    // Ecriture de la trame
    ecrire_trame_chat(trame, reponse, taille);

    // Envoi de la trame
    // p(MUTEX_LIST); deja effectue
    pt_client_cell_t ptr = client_list;
    while (ptr != NULL) {
        envoi_message_tcp(ptr->client.fd, reponse, taille);
        ptr = ptr->next;
    }
    // v(MUTEX_LIST);
}

/**** Diffusion UDP ****/

void diffuser_identite()
{
    pr_udp_identite_t trame;
    int taille = sizeof(pr_udp_identite_t);
    char message[taille];

    while (quitter_serveur == false) {
        if (partie_en_cours == false) {
            // Preparation de la trame
            trame.id_serveur = ID_SERVEUR;
            trame.port_tcp = atoi(PORT_CHAT_TCP);
            trame.port_udp_touches = atoi(PORT_TOUCHES_UDP);

            // Ecriture de la trame
            ecrire_trame_identite(&trame, message, taille);

            // Envoi de la trame
            envoi_message_udp(BROADCAST, PORT_DIFFUSION_UDP, message, taille);

#ifdef DEBUG
            printf("Sending broadcast packet of %d bytes: ", taille);
            int i;
            for (i = 0; i < sizeof(message); i++)
                printf("%02x", message[i]);
            printf("\n");
#endif
        }
        sleep(ATTENTE_DIFFUSION);
    }
}

/**** Actualisation jeu ****/

void init_laby()
{
    // Initialisation du labyrinthe
    nb_murs = dessin_vers_objets(laby, LABY_X, LABY_Y, murs);
}

void boucle_actualisation_jeu()
{
    pt_client_cell_t ptr;
    while (quitter_serveur == false) {
        if (partie_en_cours == true) {
            p(MUTEX_LIST);
            /* Gestion des missiles */
            ptr = client_list;
            while (ptr != NULL) {
                if (ptr->client.missile.tir == TIR_ACTIF) {
                    // Mise a jour de la position du missile
                    int dx = MUR_TAILLE / 10 * sin(2 * M_PI * ptr->client.missile.position.angle / 360);
                    int dz = MUR_TAILLE / 10 * cos(2 * M_PI * ptr->client.missile.position.angle / 360);
                    ptr->client.missile.position.x = ptr->client.missile.position.x + dx;
                    ptr->client.missile.position.z = ptr->client.missile.position.z + dz;

                    // Recuperation de la position du missile du client actuel
                    point p;
                    memcpy(&p, &(ptr->client.missile.position), sizeof(point));

                    /* Gestion des collisions */
                    // Collisions avec les murs
                    if (collision_objets(murs, nb_murs, p, RAYON_TIR)) {
                        // Collision avec un mur
                        desactiver_tir(&(ptr->client));
                    }
                    // Collisions avec les joueurs et les missiles
                    pt_client_cell_t tmp = client_list;
                    while (tmp != NULL) {
                        if (tmp->client.id != ptr->client.id) {
                            objet3D joueur, tir;
                            joueur_vers_objet((point*)&(tmp->client.position), &joueur);
                            tir_vers_objet((point*)&(tmp->client.missile.position), &tir);

                            if (collision_objets(&joueur, 1, p, RAYON_TIR)) {
                                // Collision avec un joueur
                                // Preparation du message
                                pr_tcp_chat_t trame;
                                char str[MAX_TAMPON_TCP];
                                strcpy(str, "");
                                if (strlen(to_cstr(&(tmp->client.pseudo))) != 0)
                                    strcat(str, to_cstr(&(tmp->client.pseudo)));
                                else
                                    strcat(str, "Anonymous");
                                strcat(str, " was shot by ");
                                if (strlen(to_cstr(&(ptr->client.pseudo))) != 0)
                                    strcat(str, to_cstr(&(ptr->client.pseudo)));
                                else
                                    strcat(str, "Anonymous");
                                strcat(str, "!");
                                trame.message = str;
                                trame.commande = CMD_MESG_ID;
                                trame.id_client = ptr->client.id;

                                // Diffusion du message
                                diffuser_message_chat(&trame);

                                // Remise au point de depart
                                set_pos(&(tmp->client.position), LABY_X / 2 * MUR_TAILLE, 0, MUR_TAILLE, 0);
                                desactiver_tir(&(ptr->client));
                            } else if (tmp->client.missile.tir == TIR_ACTIF && collision_objets(&tir, 1, p, RAYON_TIR)) {
                                // Collision avec un missile
                                desactiver_tir(&(ptr->client));
                            }
                        }
                        tmp = tmp->next;
                    }
                }
                ptr = ptr->next;
            }
            v(MUTEX_LIST);
        }
        usleep(ATTENTE_RAFRAICHISSEMENT);
    }
}

/**** Touches UDP ****/

void reception_touche(char* message, int taille, char* ip)
{
    if (partie_en_cours == true) {
        // Traduction de la trame
        pr_udp_touches_t trame;
        traduire_trame_touches(&trame, message, taille);

#ifdef DEBUG
        printf("Recieved key packet of %d bytes from %s: ", taille, ip);
        int i;
        for (i = 0; i < sizeof(message); i++)
            printf("%08x", message[i]);
        printf("\n");
        printf("touche: %d\n", trame.touches);
#endif

        p(MUTEX_LIST);
        client_t* client = get_client_by_id(&client_list, trame.id_client);
        if (client != NULL) {
            int dx = MUR_TAILLE / 10 * sin(2 * M_PI * client->position.angle / 360);
            int dz = MUR_TAILLE / 10 * cos(2 * M_PI * client->position.angle / 360);
            point p;

            // Mise a jour de la position
            switch (trame.touches) {
            case TOUCHE_DROITE:
                client->position.angle += 5;
                break;
            case TOUCHE_GAUCHE:
                client->position.angle -= 5;
                break;
            case TOUCHE_HAUT:
                p.x = client->position.x + dx;
                p.z = client->position.z + dz;
                if (!collision_objets(murs, nb_murs, p, RAYON_JOUEUR)) {
                    client->position.x += dx;
                    client->position.z += dz;
                }
                break;
            case TOUCHE_BAS:
                p.x = client->position.x - dx;
                p.z = client->position.z - dz;
                if (!collision_objets(murs, nb_murs, p, RAYON_JOUEUR)) {
                    client->position.x -= dx;
                    client->position.z -= dz;
                }
                break;
            case TOUCHE_ESPACE:
                activer_tir(client);
                break;
            default:
                break;
            }

            if (client->position.angle < 0 || client->position.angle > 360)
                client->position.angle = client->position.angle % 360;
        }
        v(MUTEX_LIST);
    }
}

/**** Graphiques UDP ****/

void calcul_graphique()
{
    pr_udp_graph_t trame;
    int taille;

    int nb_joueurs, nb_tirs;

    pt_client_cell_t ptr;
    while (quitter_serveur == false) {
        if (partie_en_cours == true) {
            p(MUTEX_LIST);
            /* Recuperation des objets 3D */
            objet3D* objets3D = malloc((nb_murs + 2 * size_of_client_list(&client_list)) * sizeof(objet3D));
            // Copie des murs
            memcpy(objets3D, murs, nb_murs * sizeof(objet3D));

            // Copie des joueurs et des missiles
            nb_joueurs = 0;
            nb_tirs = 0;
            ptr = client_list;
            while (ptr != NULL) {
                joueur_vers_objet((point*)&(ptr->client.position), &(objets3D[nb_murs + nb_joueurs + nb_tirs]));
                nb_joueurs++;
                if (ptr->client.missile.tir == TIR_ACTIF) {
                    tir_vers_objet((point*)&(ptr->client.missile.position), &(objets3D[nb_murs + nb_joueurs + nb_tirs]));
                    nb_tirs++;
                }
                ptr = ptr->next;
            }
            int nb = nb_murs + nb_joueurs + nb_tirs;

#ifdef DEBUG
            printf("---------------------------------------------\n%d walls - %d players - %d shoots:\n", nb_murs, nb_joueurs, nb_tirs);
            int i, j;
            for (i = 47; i < nb; i++) {
                if (objets3D[i].type == TYPE_MUR) {
                    printf("id %d: type mur", i);
                    for (j = 0; j < 4; j++)
                        printf(", {%d, %d, %d}", objets3D[i].p[j].x, objets3D[i].p[j].y, objets3D[i].p[j].z);
                    printf("\n");
                } else if (objets3D[i].type == TYPE_SPH) {
                    printf("id %d: type sph", t);
                    printf(", {%d, %d, %d}", objets3D[i].p[0].x, objets3D[i].p[0].y, objets3D[i].p[0].z);
                    printf(", rayon=%d\n", objets3D[i].p[1].x);
                }
            }
#endif

            /* Projection puis envoi à chaque joueur de son champ de vision */
            ptr = client_list;
            while (ptr != NULL) {
                // Copie des objets 3D avant projection
                objet3D* copie = duplique_objets(objets3D, nb);

                // Recuperation de la position du client actuel
                point p;
                memcpy(&p, &(ptr->client.position), sizeof(point));
                int angle = ptr->client.position.angle;

                // Projection graphique des murs
                decale_objets(copie, nb, p);
                rotation_objets(copie, nb, angle);
                tri_objets(copie, nb);

                // Projection graphique des joueurs et des tirs
                objet2D* objets = malloc(nb * sizeof(objet2D));
                int no;
                projete_objets(copie, nb, objets, &no);

                // Preparation de la trame
                trame.nb_objets = no;
                trame.objets = (objet_2d_t*)objets;
                taille = sizeof(trame.nb_objets) + no * sizeof(objet2D);
                char message[taille];

                // Ecriture de la trame
                ecrire_trame_graphique(&trame, message, taille);

                // Envoi de la trame
                envoi_message_udp(to_cstr(&(ptr->client.ip)), PORT_GRAPHIQUE_UDP, message, taille);

                free(copie);
                free(objets);

                ptr = ptr->next;
            }

            free(objets3D);
            v(MUTEX_LIST);
        }
        usleep(ATTENTE_GRAPHIQUE);
    }
}
