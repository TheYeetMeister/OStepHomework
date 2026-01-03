#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main() {
    int pipefd[2];
    char buf;

    if (pipe(pipefd) == -1) {
        printf("ERROR WITH CREATING PIPE\n");
        exit(1);
    }

    int forkPid = fork();

    if (forkPid == 0) {
        close(pipefd[0]);

        char* text = "Funny widdle text that makes n";
        write(pipefd[1], text, strlen(text));
        close(pipefd[1]);
        exit(0);
    } else {
        wait(NULL);
    }

    forkPid = fork();

    if (forkPid == 0) {
        close(pipefd[1]);

        char* text = "o sense by iself\n";

        while (read(pipefd[0], &buf, 1) > 0) {
            printf("%c", buf);
        }

        printf("%s", text);
        close(pipefd[0]);
        wait(NULL);
    }
}