#include <stdio.h>
#include <unistd.h>

int main() {
    pid_t pid = fork(); // Fork a child process
    //pid_t is a C datatype for storing process id.its more portable than int bcz int can store a specific integer length while pid_t can store any process integer length
    //so for storing process if we should use pid_t bcz process id length is different for different system and pid_t automatically handles all
    if (pid < 0) {
        fprintf(stderr, "Fork failed\n");
        return 1; 
    } else if (pid > 0) {
        // Parent process - exit immediately
        printf("Child process id: %d\n", pid);
        return 0;
    }

    // Child process continues here...
    setsid(); // Become a session leader (detach from current terminal so that if the terminal closes the process doesnot get close"

    // Closing standard file descriptors to avoid any interaction with terminal like reading from terminal and write output to terminal
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    while (1) {
       // sleep(1); // Sleep for 1 seconds
    }

    return 0; 
}
