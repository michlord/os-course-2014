#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

char invertCase(char c) {
    if (islower(c)) {
        return toupper(c);
    }
    return tolower(c);
}

int main() {
    int c;
    
    printf("task1_helper2\n");
    
    while ((c = getchar()) != '\n') {
        putchar(invertCase(c));
        fflush(stdout);
    }
    
    // while(1) {
        // putchar('x');
        // fflush(stdout);
    // }
    
    return EXIT_SUCCESS;
}