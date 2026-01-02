#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>

int main() {
    int fd = open("../../e.g.g.m.a.n.txt", O_RDONLY);
    int writeFd = open("sandbox/stuff.txt", O_CREAT | O_TRUNC | O_WRONLY | O_TRUNC);

    char buffer[100];

    if (fd < 0) {
        perror("There was an error opening the banger song lyrics!");
        exit(1);
    }

    //begin creating child process
    int forkPid = fork();
    int currPid = getpid();

    int bytes_read = read(fd, buffer, sizeof(buffer) - 1);
    if (bytes_read > 0) {
        buffer[bytes_read] = '\0';

        if (forkPid == 0) {
            printf("CHILD PROCESS %d\n\n", currPid);
        } else {
            printf("PARENT PROCESS %d\n\n", currPid);
        }

        printf("%s\n", buffer);
    }

    if (forkPid == 0) {
        char* writeTxt = "CHILD WROTE\n";

        write(writeFd, writeTxt, strlen(writeTxt));
    } else {
        char* writeTxt = "PARENT WROTE\n";

        write(writeFd, writeTxt, strlen(writeTxt));
    }

    if (forkPid != 0) {
        wait(NULL);
        close(fd);
        close(writeFd);
    }
}