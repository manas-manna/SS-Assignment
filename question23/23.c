#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h> 

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        fprintf(stderr, "Fork failed\n");
        return 1;
    } else if (pid == 0) {
        // Child process
        printf("Child process (PID %d) exiting...\n", getpid());
        return 0; // Child process terminates
    } else {
        // Parent process
        printf("Parent process (PID %d) created child with PID %d\n", getpid(), pid);
        sleep(20); // Sleep for a while to allow the child to terminate and become a zombie

        // check the process status using 'ps' in another terminal while the parent is sleeping
        // It will show the child process in a 'Z' (zombie) state

        int status;
        waitpid(pid, &status, 0); // Wait for the child process to terminate (clean up the zombie)
        printf("Child process has terminated. Parent exiting.\n");
    }

    return 0;
}
