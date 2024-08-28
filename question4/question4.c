#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h> // For error handling

int main() {
    int file_descriptor;
    // Open the file in read-write mode
    file_descriptor = open("demo.txt", O_RDWR);

    if (file_descriptor == -1) {
        perror("open in (read-write)");
        return 1;
    }

    printf("File opened successfully in read-write mode. File descriptor: %d\n", file_descriptor);

    // with O_EXCL.it should fail bcz the file is already present
    int excl = open("demo.txt", O_RDWR | O_EXCL);

    if (excl == -1) {
        if (errno == EEXIST) {   //EEXIST is file exit error
            printf("O_EXCL: File already exists.\n");
        } else {
            perror("open (O_EXCL)");
            return 1;
        }
    } else {
        printf("This shouldn't happen. File opened unexpectedly.\n");
        close(excl);
        return 1;
    }

    close(file_descriptor);

    return 0;
}
