#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        // Fork failed
        fprintf(stderr, "Fork failed\n");
        exit(EXIT_FAILURE);  //can use exit(1) also. EXIT_FAILURE will give 1 here. But its portable bcz not all OS represents 1 as failure
    } else if (pid == 0) {
        // Child process

       //can do some work here like here it is sleeping
        sleep(5);

        printf("Child process exiting\n");
        exit(EXIT_SUCCESS);
    } else {
        // Parent process
        printf("Parent process (PID: %d) created child with PID: %d\n", getpid(), pid);
        exit(EXIT_SUCCESS); // Parent exits immediately, making the child an orphan
    }

    return 0; // This line is never reached
}
