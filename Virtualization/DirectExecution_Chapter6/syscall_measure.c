#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>

const int NUMBER_OF_EXECUTION_TIMES = 17;

int main() {
    int fd = open("../../e.g.g.m.a.n.txt", O_RDONLY);
    char buf[0];

    int beg = clock();

    for (int i = 0; i < NUMBER_OF_EXECUTION_TIMES; ++i) {
        read(fd, buf, 0);
    }

    double elapsedTime = clock() - beg;

    printf("Full time to execute %d read calls: %f seconds\n", NUMBER_OF_EXECUTION_TIMES, elapsedTime);
    printf("Approximately %f seconds\n", elapsedTime / NUMBER_OF_EXECUTION_TIMES);
}
