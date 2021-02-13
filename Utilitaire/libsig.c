#include "libsig.h"

void init_sig() {
    action.sa_handler = handle_sig;
    sigaction(SIGINT, &action, NULL);
}

void handle_sig(int sig) {
    if (sig == SIGINT) {
        // Action à faire
    } else {
        fprintf(stderr, "Signal error!\n");
        exit(-1);
    }
}
