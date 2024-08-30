#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    const char *filename = "locktest.txt";
    int fd;
    struct flock lock; //it is data structure to store locking information like type of lock,region and other details about lock

    fd = open(filename, O_RDWR | O_CREAT, 0644);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    // Initialize the flock structure for write lock
    lock.l_type = F_WRLCK; // Write lock
    lock.l_whence = SEEK_SET; // Lock from the beginning of the file
//l_whence specifies how to interpret the l_start offset(relative to the begining of the file(SEEK_SET) or current file position(SEEK_CUR) or to the end of the file(SEEK_END)
    lock.l_start = 0;        // Start at offset 0
    lock.l_len = 0;          // Lock the entire file (0 means to the end)

    // Attempt to acquire the write lock (blocking)
    printf("Trying to acquire write lock...\n");
    if (fcntl(fd, F_SETLKW, &lock) == -1) { // F_SETLKW waits (blocks) until the lock is acquired
        perror("fcntl (write lock)");
        close(fd);
        return 1;
    }

    printf("Acquired write lock!\n");
    // can perform write operations on the file here
    sleep(10); // Simulating some work by sleeping this process for 10seconds

    // Release the write lock
    lock.l_type = F_UNLCK;
    if (fcntl(fd, F_SETLK, &lock) == -1) {
        perror("fcntl (unlock)");
        close(fd);
        return 1;
    }
//F_SETLKW is used for blocking locks(waits until the lock is acquired)
//F_SETLK is used for non-blocking locks(fails if the lock cant be acquired)
    printf("Released write lock.\n");

    // Now, let's try a read lock (non-blocking)
    lock.l_type = F_RDLCK; // Read lock

    printf("Trying to acquire read lock...\n");
    if (fcntl(fd, F_SETLK, &lock) == -1) { // F_SETLK fails immediately if the lock can't be acquired
        perror("fcntl (read lock)");
        // In a real application, you might retry or handle the situation gracefully
    } else {
        printf("Acquired read lock!\n");
        // ... Perform read operations on the file here ...
        sleep(5);

        // Release the read lock
        lock.l_type = F_UNLCK;
        if (fcntl(fd, F_SETLK, &lock) == -1) {
            perror("fcntl (unlock)");
            close(fd);
            return 1;
        }

        printf("Released read lock.\n");
    }

    close(fd);
    return 0;
}
