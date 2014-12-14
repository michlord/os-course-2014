#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <errno.h>
#include <unistd.h>

int fd_is_valid(int fd) {
    return fcntl(fd, F_GETFD) != -1 || errno != EBADF;
}

void open_and_close() {
    int fd, flags = O_RDONLY;
    char fname[] = "tmp.txt";
    
    fd = open(fname, flags);
    if (fd == -1) {
        perror("Open failed");
        exit(EXIT_FAILURE);
    }
    
    pid_t cpid = fork();
    if (cpid == -1) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    } else if (cpid == 0) {
        sleep(1);
        printf("Is file still open: %d\n", fd_is_valid(fd));
        if (close(fd) == -1) {
            perror("Close failed");
            exit(EXIT_FAILURE);
        }
        printf("Last ref closed: %d\n", !fd_is_valid(fd));
        exit(EXIT_SUCCESS);
    } else {
        if (close(fd) == -1) {
            perror("Close failed");
            exit(EXIT_FAILURE);
        }
        printf("File closed.\n");
        if(wait(NULL) == -1) {
            perror("Wait failed");
            exit(EXIT_FAILURE);
        }
    }
}

void read_offset() {
    int fd, flags = O_RDONLY;
    char fname[] = "tmp.txt";
    
    fd = open(fname, flags);
    //printf("fd=%d\n",fd);
    if (fd == -1) {
        perror("Open failed");
        exit(EXIT_FAILURE);
    }
    
    pid_t cpid = fork();
    if (cpid == -1) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    } else if (cpid == 0) {
        printf("File offset before read: %lld\n",
                (long long) lseek(fd, 0, SEEK_CUR));
        
        /*Do the read.*/
        char buff[32] = {0};
        int r = 0;
        //printf("fd=%d\n",fd);
        r = read(fd, buff, 27);
        if (r == -1) {
            perror("Read failed");
            exit(EXIT_FAILURE);
        }
        printf("Read: %s\n", buff);
        
        printf("File offset after read: %lld\n",
                (long long) lseek(fd, 0, SEEK_CUR));
        
        
        if (close(fd) == -1) {
            perror("Close failed");
            exit(EXIT_FAILURE);
        }
        exit(EXIT_SUCCESS);
    } else {
        if(wait(NULL) == -1) {
            perror("Wait failed");
            exit(EXIT_FAILURE);
        }
        
        /*Observe that the offset has changed.*/
        printf("File offset in parent: %lld\n",
                (long long) lseek(fd, 0, SEEK_CUR));
        
        if (close(fd) == -1) {
            perror("Close failed");
            exit(EXIT_FAILURE);
        }
    }
}

int main() {

    open_and_close();
    
    read_offset();

    exit(EXIT_SUCCESS);
}