/**** Bibliotheque des clients  ****/

#ifndef _LIBCLIENT_H_
#define _LIBCLIENT_H_

/** Fichiers d'inclusion des bibliothèques **/

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>

#include "libstr.h"

/** Constantes **/

#define MAX_SIZE_PSEUDO 16

/** Variables **/

typedef struct client_s client_t;
struct client_s {
    int fd;
    String pseudo;
    pos_t position;
};

/** Prototypes **/

void init_client(client_t *client);
void destroy_client(client_t *client);
void print_client(client_t *client);
void set_client(int fd, char *pseudo, pos_t *position);

#endif
