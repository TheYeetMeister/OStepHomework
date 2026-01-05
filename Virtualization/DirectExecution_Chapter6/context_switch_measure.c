#define _GNU_SOURCE
#include <stdio.h>
#include <sched.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>

const int loops = 10000;

int calMicroSecs(struct timeval time) {
    return 1000000 * time.tv_sec + time.tv_usec;
}

int main() {
    struct timeval time_before, time_after;

    int first_pipe[2];
    int second_pipe[2];
    cpu_set_t cpu_set;
    CPU_ZERO(&cpu_set);
    CPU_SET(0, &cpu_set);


    if(pipe(first_pipe) < 0 || pipe(second_pipe) < 0) {
        printf("Error with setting up pipe\n");
        exit(1);
    }

    int forkNum = fork();

    if (forkNum < 0) {
        printf("Fork failed\n");
    } else if (forkNum == 0) {
        sched_setaffinity(getpid(), sizeof(cpu_set_t), &cpu_set);

        for (int i = 0; i < loops; ++i) {
            write(first_pipe[0], NULL, 0);
            read(second_pipe[1], NULL, 0);
        }
    } else {
        sched_setaffinity(getpid(), sizeof(cpu_set_t), &cpu_set);

        gettimeofday(&time_before, NULL);
        for(int i = 0; i < loops; ++i) {
            write(second_pipe[0], NULL, 0);
            read(first_pipe[1], NULL, 0);
        }
        gettimeofday(&time_after, NULL);
        
        printf("Full time to run %d loops is %d microseconds!\n", loops, calMicroSecs(time_after) - calMicroSecs(time_before));
        printf("Average time of context switch is : %f microSeconds\n", (calMicroSecs(time_after) - calMicroSecs(time_before)) / (float) loops);
        wait(NULL);
    }

    return 0;
}