#include <sys/types.h>
#include <sys/wait.h> // wait()
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h> // exit()

int main() {
    pid_t pid; char aux; int status;
    pid = fork();

    if (pid < 0) { // error when creating new process
        fprintf(stderr, "Fork Failed\n");
        return 1;
    }
    else if (pid == 0) { // Son-process
        printf("Son: %d\t%d\n", getpid(), getppid());
        scanf("%c", &aux);
        exit(1);
    }
    else { // Father-process
        printf("Father: %d\t%d\n", getpid(), pid);
        for(int i=0; i<30; i++){
            printf("Father loop: %d/29\n", i);
            sleep(1);
        }

        aux = wait(&status);
        if(aux == pid && status == 0){
            printf("Child finished!\n");
        }
        else{
            printf("aux: %d\tstatus: %d\n", aux, status);
        }

        printf("Father end!\n");

    }
    return 0;
}
