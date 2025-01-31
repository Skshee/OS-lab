#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    pid_t p = fork(); 

    if (p < 0) {
        // Error handling for fork failure
        perror("Fork failed");
        return 1;
    } else if (p == 0) {
        // This block is executed by the child process
        printf("Child Process:\n");
        printf("Child PID: %d\n", getpid());
        printf("Parent PID: %d\n", getppid());
      
    } else {
        printf("Parent Process:\n");
        printf("Parent PID: %d\n", getpid());
        printf("Child PID: %d\n", p);
    }

    printf("Process %d is exiting.\n", getpid());
    return 0; // Return success
}
