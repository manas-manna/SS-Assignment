#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 1024 

int main() {
    const char *filename = "file.txt";
    int fd;
    ssize_t bytes_read, total_read = 0;
    char buffer[BUFFER_SIZE];

    fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    while ((bytes_read = read(fd, buffer + total_read, BUFFER_SIZE - total_read)) > 0) {
        total_read += bytes_read;

        // Process the buffer, looking for newlines
        for (int i = 0; i < total_read; i++) {
            if (buffer[i] == '\n') {
                write(STDOUT_FILENO, buffer, i + 1); 
                // Shift the remaining data to the beginning of the buffer manually
                for (int j = i + 1; j < total_read; j++) {
                    buffer[j - (i + 1)] = buffer[j];
                }
                total_read -= i + 1;
                i = -1; // Reset i to start from the beginning of the shifted data
            }
        }
    }

    if (bytes_read == -1) {
        perror("read");
        close(fd);
        return 1;
    }

    // Print any remaining data in the buffer
    if (total_read > 0) {
        write(STDOUT_FILENO, buffer, total_read);
    }

    close(fd);
    return 0;
}
