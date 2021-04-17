/** Fichiers d'inclusions **/

#include "libsig.h"

/** Variables **/

struct sigaction action_sig;
void* (*handle_sig_func)(void*);

/** Fonctions **/

void init_sig(void* (*task)(void*))
{
    action_sig.sa_handler = handle_sig;
    sigaction(SIGINT, &action_sig, NULL);

    handle_sig_func = task;
}

void handle_sig(int sig)
{
    if (sig == SIGINT) {
        handle_sig_func(NULL);
    } else {
        fprintf(stderr, "Signal error!\n");
        exit(-1);
    }
}
