#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>

#define MAX 100
#define OUTPUT "./rs.txt"

int dist_run(int dist_size, off_t offset, int *pip) {
    int i;
    int procd;
    int total_sum = 0;

    /* Position pointer within offset to read */
    if (lseek(STDIN_FILENO, offset, SEEK_SET) < 0)
        return 0;

    /* Buffer to hold the bytes of numbers */
    char buff[dist_size * sizeof(int)];

    /* Number of processed items */
    procd = 0;
    for (i = 0; i < dist_size; i++)
        /* Perform the read using the offset */
        if (read(STDIN_FILENO, buff, sizeof(int)))
            return 0;
        else
            procd++;

    /* Write result in pipe */
    if (write(pip[1], &procd, sizeof(int)) == -1)
        return 0;

    /* Close pipes */
    close(pip[0]);
    close(pip[1]);

    /* Build and execute command */ 
    char *comm[] = {"./add", ">", OUTPUT, NULL};
    execvp(comm[0], comm);

    /* Shouldn not arrive here. */
    return 1;
}

int main(int argc, char *argv[]) {
    /* Not enough args */
    if (argc < 3) 
        return 0;

    int i;
    int N;
    int tmp;
    int total;
    int status;
    int pip[2];
    int file_size;
    int dist_size;
    pid_t wpid;
    char *name;
    struct stat st;

    /* Get filename and N */
    name = argv[1];
    N = atoi(argv[2]);

    /* Check N bounds */
    if (N < 0 || N > MAX) 
        return 0;

    /* Get file size */
    stat(name, &st);
    file_size = st.st_size;
    
    /* Distribution size */
    dist_size = ((file_size / sizeof(int)) / N);
    /* Start offset in bytes */
    off_t offset = 0;

    /* Create pipe */
    if (pipe(pip) == -1)
        return 0;

    /* Fork processes */
    for (i = 0; i < N; i++) {
        switch (fork()) {
            case -1:
                /* Error. Get out. */
                return 0;
            
            /* Child process */
            case 0:
                dist_run(dist_size, offset, pip);
                break;
            
            default:
                break;
        }

        /* Increase offset */
        offset += dist_size * sizeof(int);
    }

    /* Close pipe that's not in use */
    close(pip[1]);

    total = 0;
    /* Read and sum */
    while (read(pip[0], &tmp, sizeof(int)) > 0)
        total += tmp;

    /* Wait for all children processes to finish */
    while ((wpid = wait(&status)) > 0);

    return total;
}