#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>

int main() {
    const char *filename = "sharedfile.txt";
    int fd;

    fd = open(filename, O_RDWR | O_CREAT | O_APPEND, 0644);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        close(fd);
        return 1;
    } else if (pid == 0) {
        // Child process
        const char *child_data = "Written by child process\n";
        write(fd, child_data, strlen(child_data));
    } else {
        // Parent process
        const char *parent_data = "Written by parent process\n";
        write(fd, parent_data, strlen(parent_data));
    }

    close(fd); // Both parent and child close the file descriptor

    // Display the file contents
    system("cat sharedfile.txt"); 
  
    return 0;
}
