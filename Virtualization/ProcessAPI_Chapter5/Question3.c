#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

volatile sig_atomic_t childFinished = 0;

void printGoodbye(int sig) {
    printf("goodbye\n");
    childFinished = 1;
}

int main() {
    signal(SIGUSR1, printGoodbye);

    int mainPid = getpid();
    int forkPid = fork();

    if (forkPid == 0) {
        //child process
        printf("hello\n");
        kill(mainPid, SIGUSR1);
    } else {
        while (!childFinished) {
            sleep(1);
        }
    }
}