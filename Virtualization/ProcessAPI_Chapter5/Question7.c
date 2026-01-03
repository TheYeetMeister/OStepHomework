#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int forkPid = fork();

    if (forkPid == 0) {
        fclose(stdout);
        printf("Child just tried to print to stdout after closing it");
    } else {
        wait(NULL);
    }
}