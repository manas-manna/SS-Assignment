#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>


int main() {
    const char *filename = "file1.txt";
    int fd;
    off_t offset;

    // Open the file in read-write mode, create if it doesn't exist
    fd = open(filename, O_RDWR | O_CREAT, 0644);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    // Write 10 bytes
    char *data1 = "First 10";
    if (write(fd, data1, 10) != 10) {
        perror("write 1");
        close(fd);
        return 1;
    }

    // Move the file pointer by 10 bytes
    offset = lseek(fd, 10, SEEK_CUR);
    if (offset == -1) {
        perror("lseek");
        close(fd);
        return 1;
    } 

    printf("New file offset after lseek: %lld\n", (long long) offset);

    // Write another 10 bytes
    char *data2 = "Next 10";
    if (write(fd, data2, 10) != 10) {
        perror("write 2");
        close(fd);
        return 1;
    }

    // Close the file
    close(fd);

    // Use 'od' to check the file contents (you'll need to run this in the terminal)
    system("od -c file1.txt"); 

    return 0;
}
