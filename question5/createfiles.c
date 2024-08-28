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

    int i = 0;
    while (1) {
        char filename[20];
        snprintf(filename, 20, "new_file_%d.txt", i++); 
	//here 20 indicates that we are telling snprintf that the maximum size of filename is 20chars
	//it will prevent to make a very large file name than 20 characters.It will truncate down to 
	//20 characters if the file name is becomes more than  20 characters long
        int fd = creat(filename, 0644);
        if (fd == -1) {
            perror("creat");
            continue; //we can also break the loop if we are getting a error
        }

        sleep(5); // create a new file in every 5 seconds
	close(fd);
    }

    return 0; 
}
