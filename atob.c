#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int i, n, stat, procd;
    char inbuff[5];
    char outbuff[20];

    procd = 0;
    while (stat = (read(STDIN_FILENO, inbuff, sizeof(int))) > 0) {
        if (stat == -1)
            return 0;
        n = atoi(inbuff);
        if (write(STDOUT_FILENO, &n, sizeof(n)) == -1)
            return 0;
        procd++;
    }

    return procd;
}