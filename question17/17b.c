#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    const char *filename = "tickets.txt";
    int fd;
    struct flock lock;
    int ticket_number;
    // Open the file in read-write mode
    fd = open(filename, O_RDWR);
    if (fd == -1) {
        perror("open");
        return 1;
    }
FILE *fp = fdopen(fd, "r+");
    if (fp == NULL) {
        perror("fdopen");
        close(fd);
        return 1;
    }

    // Initialize the flock structure for write lock
    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0;

    // Acquire the write lock (blocking)
    if (fcntl(fd, F_SETLKW, &lock) == -1) {
        perror("fcntl (write lock)");
        close(fd);
        return 1;
    }

    // Read the current ticket number from the file
    if (fscanf(fp, "%d", &ticket_number) != 1) {
        perror("fscanf");
        fclose(fp);
        return 1;
    }

    // Increment the ticket number
    ticket_number++;

    // Rewind the file pointer to the beginning
    if (lseek(fd, 0, SEEK_SET) == -1) {
        perror("lseek");
        close(fd);
        return 1;
    }

    // Write the updated ticket number back to the file
    if (dprintf(fd, "%d\n", ticket_number) < 0) {
        perror("dprintf");
        close(fd);
        return 1;
    }

    // Release the write lock
    lock.l_type = F_UNLCK;
    if (fcntl(fd, F_SETLK, &lock) == -1) {
        perror("fcntl (unlock)");
        close(fd);
        return 1;
    }

    fclose(fp);
    printf("Your ticket number is: %d\n", ticket_number);
    return 0;
}
