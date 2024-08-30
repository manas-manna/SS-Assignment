#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    const char *filename = "locktest.txt"; 
    int fd;
    struct flock lock;

    // Open the file (create if it doesn't exist)
    fd = open(filename, O_RDWR | O_CREAT, 0644);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    // Define the region to lock (adjust these values as needed)
    off_t start_offset = 10; // Lock starts at byte offset 10
    off_t lock_length = 20;  // Lock a region of 20 bytes
  //we  can directly store the values 10 and 20 to the l_start and l_len.But its preferered to use off_t bbcz it is platform independent and can store any amount of offset value
    
// Initialize the flock structure for write lock
    lock.l_type = F_WRLCK;   // Write lock
    lock.l_whence = SEEK_SET; // Lock from the beginning of the file
    lock.l_start = start_offset;
    lock.l_len = lock_length;

    // Attempt to acquire the write lock (blocking)
    printf("Trying to acquire write lock on bytes %lld-%lld...\n", 
           (long long) start_offset, (long long) (start_offset + lock_length - 1));
    if (fcntl(fd, F_SETLKW, &lock) == -1) {
        perror("fcntl (write lock)");
        close(fd);
        return 1;
    }

    printf("Acquired write lock!\n");
    // can perform write operations on the locked region
    sleep(10); // Simulatign write operation

    // Release the write lock
    lock.l_type = F_UNLCK;
    if (fcntl(fd, F_SETLK, &lock) == -1) {
        perror("fcntl (unlock)");
        close(fd);
        return 1;
    }

    printf("Released write lock.\n");

    // read lock (non-blocking)
    lock.l_type = F_RDLCK; // Read lock

    printf("Trying to acquire read lock on bytes %lld-%lld...\n", 
           (long long) start_offset, (long long) (start_offset + lock_length - 1));
    if (fcntl(fd, F_SETLK, &lock) == -1) {
        perror("fcntl (read lock)");
        //error
    } else {
        printf("Acquired read lock!\n");
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
