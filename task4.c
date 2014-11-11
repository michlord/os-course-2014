/* http://www.gnu.org/software/libc/manual/html_node/Launching-Jobs.html */
/* http://cboard.cprogramming.com/c-programming/118168-creating-child-process-then-killing.html */

#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <signal.h>
#include <sys/wait.h>
#include <errno.h>
#include <sys/time.h>
#include <sys/resource.h>

#define CHILDREN_LIMIT 100

int main() {
    /*
     * The  RLIMIT_NPROC limit, which places a limit on the number of
     * processes that can be created, is a good example of the rationale for this approach.
     * Applying this limit against only the number of children that the process itself created
     * would be ineffective, since each child that the process created would also be able to
     * create further children, which could create more children, and so on. Instead, the
     * limit is measured against the count of all processes that have the same real user ID.
     * Note, however, that the resource limit is checked only in the processes where it has
     * been set .
     */
    struct rlimit rl;
    if (getrlimit(RLIMIT_NPROC, &rl) == -1){
        perror("Error getting fork limit.");
        exit(EXIT_FAILURE);
    }
    
    rl.rlim_cur = 100;
    printf("soft: %d hard: %d\n",(int)rl.rlim_cur, (int)rl.rlim_max);
    if (setrlimit(RLIMIT_NPROC, &rl)) {
        perror("Error setting fork limit.");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();
    if (pid == -1) {
        perror("Fork failed.");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        /* Children of this process will inherit
         * its pgid.
         */
        if (setpgid(0, 0) == -1) {
            perror("Setpgid failed.");
            exit(EXIT_FAILURE);
        }
        for (int i = 0; i < CHILDREN_LIMIT; ++i) {
            pid_t c_pid = fork();
            if (c_pid == -1) {
                perror("Fork child failed.");
            } else if (c_pid == 0) {
                pause();
                exit(EXIT_SUCCESS);
            }
        }
        pause();
        exit(EXIT_SUCCESS);
    } else {
        sleep(4);
        
        killpg(pid, SIGTERM);
        /*
         * A call to the wait() or waitpid() function only returns status on an
         * immediate child process of the calling process; that is, a child that was 
         * produced by a single fork() call (perhaps followed by an exec or other
         * function calls) from the parent. If a child produces grandchildren by
         * further use of fork(), none of those grandchildren nor any of their descendants
         * affect the behavior of a wait() from the original parent process.
        */
        if(wait(NULL) == -1) {
            perror("Wait failed");
            exit(EXIT_FAILURE);
        }
        printf("Parent alive...");
        getchar();
        exit(EXIT_SUCCESS);
    }
}