/**** Header client ****/

#ifndef _TEST_H_
#define _TEST_H_

/** Fichiers d'inclusion des bibliothèques **/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "libclient.h"
#include "libclientlist.h"
#include "libsig.h"
#include "libstrlist.h"
#include "libtcp.h"
#include "libthread.h"
#include "libudp.h"

/** Constantes **/

/** Variables **/

bool running = true;

/** Prototypes **/

int main(int argc, char* argv[]);
void usage();
void gestion_sig();

void tache_hello_world();
void tache_serveur_tcp(int* s);
void gestion_client_tcp(int* s);
void tache_serveur_udp(int* s);

void test_str();
void test_str_list();
void test_client();
void test_client_list();
void test_tache();
void test_serveur_tcp();
void test_serveur_udp();

#endif
