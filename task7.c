#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

extern char **environ;

void print_env(int limit) {
    for(char **p = environ; *p != NULL; ++p) {
        char *str = *p;
        printf("%s\n", str);
        if ((limit -= 1) <= 0) {
            break;
        }
    }
}

/* User has to call free(). */
char *get_current_working_dir() {
    long size;
    char *buf;
    char *ptr = NULL;
    size = pathconf(".", _PC_PATH_MAX);
    if ((buf = (char *)malloc((size_t)size)) != NULL) {
        ptr = getcwd(buf, (size_t)size);
    }
    return ptr;
}

void print_env_and_cwd() {
    printf("ENVIRONMENT:\n");
    print_env(10);
    char *cwd = get_current_working_dir();
    printf("...\n\nCURRENT WORKING DIR:\n%s\n", cwd);
}

int main() {
    int pipefd[2]; /* [0] - read end, [1] - write end. */
    pid_t cpid;
    char buf;
    
    if (pipe(pipefd) == -1) {
         perror("Pipe failed");
         exit(EXIT_FAILURE);
    }
    
    cpid = fork();
    if (cpid == -1) {
    
    } else if (cpid == 0) {
        close(pipefd[1]); /* Close unused write end. */
        while (read(pipefd[0], &buf, 1) > 0){
            printf("pipe read: %c\n", buf);
        }
        close(pipefd[0]);
        
        //print_env_and_cwd();
        
        char *cwd = get_current_working_dir();
        printf("CURRENT WORKING DIR:\n%s\n", cwd);
        
        char *env_test = getenv("test_blablabla");
        printf("test_blablabla=%s\n", env_test);
        
        
        exit(EXIT_SUCCESS);        
    } else {
        if (setenv("test_blablabla", "value_of_the_test_blablabla", 0) == -1) {
            perror("Set env failed");
            exit(EXIT_FAILURE);
        }
        if (chdir("../") == -1) {
            perror("Change dir failed");
            exit(EXIT_FAILURE);
        }
        
        char *cwd = get_current_working_dir();
        printf("CURRENT WORKING DIR:\n%s\n", cwd);
        
        char *env_test = getenv("test_blablabla");
        printf("test_blablabla=%s\n", env_test);
    
        close(pipefd[0]); /* Close unused read end. */
        char c = 'a';
        printf("Writing...");
        fflush(stdout);
        write(pipefd[1], &c, 1);
        close(pipefd[1]); /* Reader will see EOF */
        if(wait(NULL) == -1) {
            perror("Wait failed");
            exit(EXIT_FAILURE);
        }
        exit(EXIT_SUCCESS);
    }
    
    exit(EXIT_SUCCESS);
}