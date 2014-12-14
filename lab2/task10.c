#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <pthread.h>
#include <syscall.h>

#define UNUSED(x) (void)(x)

void *thread_fun(void *params) {
    UNUSED(params);
    printf("Started thread with id = %ld\n", syscall(SYS_gettid));
    sleep(10);
    return NULL;
}

#define MT_AMT 6

int main() {
    pthread_t thread_buff[MT_AMT];

    char ps_cmd_buff[255];
    pid_t pid = getpid();
    sprintf(ps_cmd_buff, "ps -Tp %d", pid);

    for (int i = 0; i < MT_AMT; ++i) {
        if (pthread_create(thread_buff + i, NULL, thread_fun, NULL) > 0) {
            perror("Thread creation failed");
        }
    }
    
    int ret = system(ps_cmd_buff);
    if (ret == - 1){
        perror("Shell command failed");
        exit(EXIT_FAILURE);
    }
    
    for (int i = 0; i < MT_AMT; ++i) {
        if (pthread_join(thread_buff[i], NULL) > 0) {
            perror("Thread joining failed");
        }
    }
    
    exit(EXIT_SUCCESS);
}

/*
 * A thread may either be joinable or detached.  If a thread is joinable, then another thread can call pthread_join(3) to wait for the  thread
 * to terminate and fetch its exit status.  Only when a terminated joinable thread has been joined are the last of its resources released back
 * to the system.  When a detached thread terminates, its resources are automatically released back to the system: it is not possible to  join
 * with  the thread in order to obtain its exit status.  Making a thread detached is useful for some types of daemon threads whose exit status
 * the application does not need to care about.  By default, a new thread is created in a joinable state, unless attr was set  to  create  the
 * thread in a detached state (using pthread_attr_setdetachstate(3)).
*/