#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>
#include <signal.h>

static int task_version_flag;

void get_options(int argc, char **argv) {
    static struct option long_options[] = 
    {
        {"version_0", no_argument, &task_version_flag, 0},
        {"version_1", no_argument, &task_version_flag, 1},
        {0, 0, 0, 0}
    };

    int option_index = 0;
    getopt_long(argc, argv, "", long_options, &option_index);
}

int main(int argc, char **argv) {
    get_options(argc, argv);
    
    /* 
    * To avoid accumulating dead children, simply tell the system
    * that you're not interested in them by setting $SIGCHLD to "IGNORE" .
    */
    if (task_version_flag == 1) {
        signal(SIGCHLD, SIG_IGN);
    }
    
    pid_t pid = fork();
    if (pid == -1) {
        fprintf(stderr, "Fork failed.");
    } else if (pid == 0) {
        /* Child process executes here. */
        pid_t child_pid = getpid();
        printf("Child pid: %d\n", child_pid);
        exit(0);
    } else {
        /* Parent process executes here. */
        pid_t parent_pid = getpid();
        printf("Parent pid: %d\n", parent_pid);
        printf("Sleep for one second.\n");
        sleep(1);
        
        char pid_str[16];
        sprintf(pid_str, "%d", pid);
        int exec_res = execl("/bin/ps", "pid_str" , "-o", "pid,ppid,stat,cmd", (char *) NULL);
        if (exec_res == -1) {
            fprintf(stderr, "Error calling ps.");
        }
        /* The Z+ STAT entry indicates that the process is a zombie. */
    }
    
    return 0;
}