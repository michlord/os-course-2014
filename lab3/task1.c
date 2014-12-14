#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>
#include <errno.h>

#define CHILD_TO_PARENT 0
#define PARENT_TO_CHILD 1

static int variant = CHILD_TO_PARENT;

void get_options(int argc, char **argv) {
    int c;
    while ((c = getopt(argc, argv, "r")) != -1) {
        switch (c) {
            case 'r' :
                variant = PARENT_TO_CHILD;
                break;
        }
    }
}

typedef struct pinfo {
    FILE         *file;
    pid_t         pid;
    struct pinfo *next;
} pinfo;

pinfo *plist = NULL;

void add_pinfo(pinfo **list, FILE *file, pid_t pid) {
    pinfo *cur;
    if (*list == NULL) {
        *list = malloc(sizeof(pinfo));
        cur = *list;
    } else {
        cur = *list;
        while(cur->next != NULL) {
            cur = cur->next;
        }
        cur->next = malloc(sizeof(pinfo));
        cur = cur->next;
    }
    cur->file = file;
    cur->pid = pid;
    cur->next = NULL;
}

pinfo *remove_pinfo(pinfo **list, FILE *file) {
    pinfo *old = *list;
    pinfo *cur = *list;
    if (cur == NULL) {
        return NULL;
    }
    if (cur->next == NULL) {
        if (cur->file == file) {
            *list = NULL;
            return cur;
        }
    }
    while(cur != NULL) {
        if (cur->file == file) {
            old->next = cur->next;
            return cur;
        }
        old = cur;
        cur = cur->next;
    }
    return NULL;
}

FILE *my_popen(const char *path, const char *type) {
    int pipefd[2]; /* [0] - read end, [1] - write end. */
    pid_t cpid;
    
    char *argv[1] = {(char*)0};
    char *envp[1] = {(char*)0};

    if (pipe(pipefd) == -1) {
        return NULL;
    }
    
    cpid = fork();
    
    if (cpid == -1) {
        close(pipefd[0]);
        close(pipefd[1]);
        return NULL;
    }
    
    if (type[0] == 'r') {
        if (cpid == 0) {
            /* child */
            
            /* Close unused read end. */
            close(pipefd[0]); 
            
            /* Bind fd 1 (standard output) to the write end of the pipe. */
            dup2(pipefd[1],1);
            
            /* Close original fd we got from the pipe(). */
            close(pipefd[1]);
            
            /* Execute the cmd. */
            execve(path, argv, envp);
            
            /* execve() only returns on error. */
            return NULL;
        } else {
            /* parent */
            
            /* Close unused write end. */
            close(pipefd[1]);
            
            /* Associate a stream with the existing file descriptor.*/
            FILE *file = fdopen(pipefd[0], "r");
            add_pinfo(&plist, file, cpid);
            return file;
        }
    } else if (type[0] == 'w') {
        if (cpid == 0) {
            /* child */
            
            /* Close unused write end. */
            close(pipefd[1]); 
            
            /* Bind fd 0 (standard input) to the read end of the pipe. */
            dup2(pipefd[0],0);
            
            /* Close original fd we got from the pipe(). */
            close(pipefd[0]);
            
            /* Execute the cmd. */
            execve(path, argv, envp);
            
            /* execve() only returns on error. */
            return NULL;
        } else {
            /* parent */
            
            /* Close unused read end. */
            close(pipefd[0]);
            
            /* Associate a stream with the existing file descriptor.*/
            FILE *file = fdopen(pipefd[1], "w");
            add_pinfo(&plist, file, cpid);
            return file;
        }
    } else {
        return NULL;
    }
}

int my_pclose(FILE *stream) {
    pid_t pid;
    int status;
    pinfo *p = remove_pinfo(&plist, stream);
    
    if (p == NULL) {
        errno = ECHILD;
        return -1;
    }
    fclose(stream);
    if(kill(p->pid, SIGHUP) == -1) {
        free(p);
        perror("Kill failed");
        return -1;
    }
    
    do {
        pid = waitpid(p->pid, &status, 0);
    } while (pid == -1 && errno == EINTR);
    
    free(p);
    
    if (WIFEXITED(status)) {
        return WEXITSTATUS(status);
    }
    
    if (WIFSIGNALED(status)) {
        return WTERMSIG(status);
    }
    return -1;
}

char invertCase(char c) {
    if (islower(c)) {
        return toupper(c);
    }
    return tolower(c);
}

int main(int argc, char **argv) {
    FILE* file = NULL;
    int c;
    
    get_options(argc, argv);
    
    if (variant == CHILD_TO_PARENT) {
        file = my_popen("/home/michlord/operating_systems/lab3/task1_helper1", "r");
        if (file == NULL) {
            perror("Pipe open failed");
            exit(EXIT_FAILURE);
        }
        while ((c = fgetc(file)) != EOF) {
            putchar(invertCase(c));
        }
    } else {
        file = my_popen("/home/michlord/operating_systems/lab3/task1_helper2", "w");
        if (file == NULL) {
            perror("Pipe open failed");
            exit(EXIT_FAILURE);
        }
        fprintf(file, "Hello World!\n");
        fflush(file);
    }
    sleep(1);
    
    int res;
    if ((res = my_pclose(file)) == -1) {
        perror("pclose failed");
        exit(EXIT_FAILURE);
    }
    printf("\nexit status: %d\n", res);
    
    return EXIT_SUCCESS;
}