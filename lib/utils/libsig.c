#include "libsig.h"

void init_sig() {
    action_sig.sa_handler = handle_sig;
    sigaction(SIGINT, &action_sig, NULL);
}

void handle_sig(int sig) {
    if (sig == SIGINT) {
        // TODO: Action à faire
        
    } else {
        fprintf(stderr, "Signal error!\n");
        exit(-1);
    }
}
