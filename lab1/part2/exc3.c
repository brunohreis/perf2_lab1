#include <sys/types.h>
#include <sys/wait.h> // wait()
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h> // exit()
#include <signal.h>
#include <string.h>

#define BUFFER_SIZE 100

int main() {
    pid_t pid; char aux; int status;
    int fd[2];
    char buffer[BUFFER_SIZE];

    if (pipe(fd) == -1) {
        return 1;
    }

    pid = fork();

    if (pid < 0) { // error when creating new process
        fprintf(stderr, "Fork Failed\n");
        return 1;
    }
    else if (pid == 0) { // Son-process
        close(fd[1]);

        // waits until the father writes something to the pipe, and then reads it
        read(fd[0], buffer, BUFFER_SIZE);

        printf("Son's output: %s\n", buffer);

        close(fd[0]);
    }
    else { // Father-process
        close(fd[0]);

        printf("Father's input: ");
        scanf("%s", buffer);
        write(fd[1], buffer, strlen(buffer) + 1);

        close(fd[1]);

        wait(NULL);
    }
    return 0;
}
