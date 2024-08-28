#include <stdio.h>
#include <fcntl.h>  // For file control operations
#include <unistd.h>

int main() {
    int file_descriptor;

    // Create the file with read/write permissions(0600) for the owner
    file_descriptor = creat("filedescriptor", 0600); 

    if (file_descriptor == -1) { //returns either -1 or nonnegative integer
        perror("creat"); 
        return 1;
    }

    printf("File created. File descriptor: %d\n", file_descriptor);

    //closing the file descriptor
    close(file_descriptor);

    return 0;
}
