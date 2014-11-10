#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <signal.h>
#include <stdio.h>

#define UNUSED(x) (void)(x)

struct sigaction oldact_sigterm;

void sig_term_handler(int sig) {
    UNUSED(sig);
    printf("SIGTERM intercepted.\n");
    fflush(stdout);

    sigaction(SIGTERM, &oldact_sigterm, NULL);
}

int main() {
    pid_t cpid = fork();
    if (cpid == -1) {
        perror("Fork failed");
    } else if (cpid == 0) {
        struct sigaction sigchld_action_1 = {
            .sa_handler = sig_term_handler
        };
        struct sigaction sigchld_action_2 = {
            .sa_handler = SIG_IGN
        };
        sigaction(SIGTERM, &sigchld_action_1, &oldact_sigterm);
        sigaction(SIGINT, &sigchld_action_2, NULL);
        pause(); //SIGTERM 1
        pause(); // SIGINT 1 (no action) SIGTERM and it doesn't even enter next pause();
        pause();
        exit(EXIT_SUCCESS);
    } else {
        sleep(1);
        kill(cpid, SIGTERM);
        sleep(1);
        kill(cpid, SIGINT);
        sleep(1);
        kill(cpid, SIGKILL);
        wait(NULL);    
    }
    exit(EXIT_SUCCESS);
}