#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void printIdentifier(char* text) {
    printf("%s CALL:\n\n", text);
}

int main() {
    int forkPid = fork();

    if (forkPid == 0) {
        printIdentifier("execl");
        execl("/bin/ls", "ls");
        exit(0);
    } else {
        wait(NULL);
    }

    forkPid = fork();

    if (forkPid == 0) {
        printIdentifier("execle");
        execle("/bin/ls", "ls");
        exit(0);
    } else {
        wait(NULL);
    }

    forkPid = fork();

    if (forkPid == 0) {
        printIdentifier("execlp");
        execlp("/bin/ls", "ls");
        exit(0);
    } else {
        wait(NULL);
    }

    char* args[] = {"ls", NULL};
    forkPid = fork();

    if (forkPid == 0) {
        printIdentifier("execv");
        execv("/bin/ls", args);
        exit(0);
    } else {
        wait(NULL);
    }

    forkPid = fork();

    if (forkPid == 0) {
        printIdentifier("execvp");
        execvp("/bin/ls", args);
        exit(0);
    } else {
        wait(NULL);
    }

    forkPid = fork();

    if (forkPid == 0) {
        printIdentifier("execvpe");
        execvpe("/bin/ls", args);
        exit(0);
    } else {
        wait(NULL);
    }
}