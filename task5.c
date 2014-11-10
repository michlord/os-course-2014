#include <stdlib.h>
#include <stdio.h>

void bye() {
    printf("Goodbye!\n");
}

int main() {
    if (atexit(bye) != 0) {
        fprintf(stderr, "Cannot set exit function.\n");
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}