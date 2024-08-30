#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t child_pids[3];

    // Create three child processes
    for (int i = 0; i < 3; i++) {
        child_pids[i] = fork();

        if (child_pids[i] < 0) {
            perror("Fork failed");
            exit(EXIT_FAILURE);
        } else if (child_pids[i] == 0) {
            // Child process
            printf("Child %d (PID: %d) is doing some work...\n", i + 1, getpid());
            sleep(i + 2); // Simulate some work (different durations for each child)
            printf("Child %d (PID: %d) is done!\n", i + 1, getpid());
            exit(EXIT_SUCCESS);
        }
    }

    // Parent process waits for child 2 and exiting after child 2 has finished
    int status;
    pid_t waited_pid = waitpid(child_pids[1], &status, 0);

    if (waited_pid == -1) {
        perror("waitpid");
        exit(EXIT_FAILURE);
    }

    printf("Parent process waited for child 2 (PID: %d)\n", waited_pid);

    

    return 0;
}
