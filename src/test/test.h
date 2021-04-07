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

#define TEST_STR 0
#define TEST_STR_LIST 1
#define TEST_CLIENT 2
#define TEST_CLIENT_LIST 3
#define TEST_TACHE 4
#define TEST_SERVEUR_TCP 5
#define TEST_SERVEUR_UDP 6

#define TEST TEST_SERVEUR_UDP

/** Variables **/

bool running = true;

/** Prototypes **/

int main(int argc, char* argv[]);
void usage();
void gestion_sig();

void tache_hello_world();
void tache_serveur_tcp(int* s);
void gestion_client_tcp(int* s);
void tache_serveur_udp(char* message, int* size, char* ip);

void test_str();
void test_str_list();
void test_client();
void test_client_list();
void test_tache();
void test_serveur_tcp(char* service);
void test_serveur_udp(char* service);

#endif
