#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int M = -1;
    if (argc > 2) {
        M = atoi(argv[2]);
    }

    int i, n, sum, stat, procd;
    char inbuff[10];
    char outbuff[50];

    sum = procd = 0;
    while (stat = (read(STDIN_FILENO, &n, sizeof(int))) > 0 || M != 0) {
        if (stat == -1)
            return 0;
        sum += n;
        procd++;
        M--;
    }

    sprintf(outbuff, "%d", sum);
    if (write(STDOUT_FILENO, outbuff, strlen(outbuff)) == -1)
        return 0;

    return procd;
}