#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        exit(-1);
    }

    int i;
    char *args[argc];
    
    for (i = 1; i < argc; i++) {
        args[i - 1] = argv[i];
    }

    args[argc - 1] = NULL;
    execvp(argv[1], args);
    exit(0);
}