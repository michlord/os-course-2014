#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>

#define VARIANT_NOT_SET -1
#define VARIANT_ABORT 0
#define VARIANT_EXIT 1
#define VARIANT_SIGNAL 2
#define VARIANT_WAIT 3
#define VARIANT_FORK 4
static int variant = VARIANT_NOT_SET;

void get_options(int argc, char **argv) {
    int c;
    while ((c = getopt(argc, argv, "aeswf")) != -1) {
        switch (c) {
            case 'a' :
                variant = VARIANT_ABORT;
                break;
            case 'e' :
                variant = VARIANT_EXIT;
                break;
            case 's' :
                variant = VARIANT_SIGNAL;
                break;
            case 'w' :
                variant = VARIANT_WAIT;
                break;
            case 'f' :
                variant = VARIANT_FORK;
                break;
        }
        if (variant != VARIANT_NOT_SET) {
            return;
        }
    }
}

void bye() {
    printf("Goodbye!\n");
}

int main(int argc, char **argv) {
    get_options(argc, argv);

    if (atexit(bye) != 0) {
        fprintf(stderr, "Cannot set exit function.\n");
        exit(EXIT_FAILURE);
    }
    
    switch (variant) {
        case VARIANT_ABORT :
            abort();
            break;
        case VARIANT_EXIT :
            exit(EXIT_SUCCESS);
            break;
        case VARIANT_SIGNAL :
            kill(0, SIGTERM);
            break;
        case VARIANT_WAIT :
            pause();
            break;
        case VARIANT_FORK : {
            for (int i = 0; i < 2; ++i) {
                pid_t pid = fork();
                if (pid == -1) {
                    perror("Fork failed");
                } if (pid == 0) {
                    printf("Child exiting.\n");
                    exit(EXIT_SUCCESS);
                } else {
                    int status;
                    wait(&status);
                    printf("Child exited.\n");
                    exit(EXIT_SUCCESS);
                }
            }
        
            break;
        }
    }
    
    exit(EXIT_SUCCESS);
}