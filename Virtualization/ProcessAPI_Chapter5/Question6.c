#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int forkPid = fork();

    int pid = getpid();
    if (forkPid == 0) {
        printf("Child process: %d\n", pid);
        exit(0);
    } else {
        printf("Parent process: %d\n", pid);
        int waitVal = waitpid(forkPid, NULL, 0);

        printf("This is the value of the waitpid() function: %d\n", waitVal);
    }
    printf("\n\n\n");

    forkPid = fork();
    pid = getpid();

    if (forkPid == 0) {
        int waitVal = waitpid(forkPid, NULL, 0);

        printf("Child Process: %d\nThis is the value of the waitpid() function: %d\n", pid, waitVal);
    } else {
        int waitVal = waitpid(forkPid, NULL, 0);

        printf("Parent Process: %d\nThis is the value of the waitpid() function: %d\n", pid, waitVal);
    }
}