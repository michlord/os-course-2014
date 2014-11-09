#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    pid_t process_id        = getpid();
    pid_t parent_process_id = getppid();
    pid_t session_id        = getsid(process_id);
    pid_t process_group_id  = getpgrp();
    
    if (session_id == -1) {
        fprintf(stderr, "Error getting session id.");
    }
    
    /* POSIX.1 version always succeeds but in case I've changed
    * it to something else later lets keep the lines below.
    */
    if (process_group_id == -1) {
        fprintf(stderr, "Error getting process group id.");
    }
    
    printf("pid: %d, ppid: %d, sid: %d, pgrp: %d\n",
           process_id, parent_process_id, session_id,
           process_group_id);
    
    /* In a separate terminal run 'ps' to see that
    *  the displayed data is correct. 
    *  ps -Ctask1 -opid -oppid -osid -opgrp
    */
    getchar();
    return 0;
}