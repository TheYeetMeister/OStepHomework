#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void printPid(int pid, int x) {
    printf("Process pid: %d, x = %d\n", pid, x);
}

int main() {
    int x = 100;

    int forkPid = fork();
    int pid = getpid();

    if (forkPid != 0) {
        //parent pid

        printf("Before change parent process ");
        printPid(pid, x);

        x = 95;

        printf("After change parent process ");
        printPid(pid, x);
    } else {
        //child pid
        
        printf("Before change child process ");
        printPid(pid, x);

        x = 105;

        printf("After change parent process ");
        printPid(pid, x);
    }
}