#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include<stdlib.h>
#define RECORD_SIZE 100

void lock_record(int fd, int record_num, int lock_type) {
    struct flock lock;
    lock.l_type = lock_type;   // F_RDLCK or F_WRLCK
    lock.l_whence = SEEK_SET; 
    lock.l_start = record_num * RECORD_SIZE;
    lock.l_len = RECORD_SIZE;

    if (fcntl(fd, F_SETLKW, &lock) == -1) { // Blocking lock
        perror("fcntl");
        close(fd);
        exit(1);
    }
}

void unlock_record(int fd, int record_num) {
    struct flock lock;
    lock.l_type = F_UNLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = record_num * RECORD_SIZE;
    lock.l_len = RECORD_SIZE;

    if (fcntl(fd, F_SETLK, &lock) == -1) { 
        perror("fcntl (unlock)");
        close(fd);
        exit(1);
    }
}

int main() {
    const char *filename = "records.txt"; 
    int fd;

    // Open the file (create if it doesn't exist)
    fd = open(filename, O_RDWR | O_CREAT, 0644);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    char *records[] = {"Record 1", "Record 2", "Record 3"};
    for (int i = 0; i < 3; i++) {
        lock_record(fd, i, F_WRLCK); // Lock the record before writing
        if (pwrite(fd, records[i], strlen(records[i]), i * RECORD_SIZE) == -1) {
            perror("pwrite");
            close(fd);
            return 1;
        }
        unlock_record(fd, i); 
    }

    // Access a record eg record number 1
    int recordno = 1;

    lock_record(fd, recordno, F_RDLCK); // Acquire read lock

    char read_buffer[RECORD_SIZE];
    if (pread(fd, read_buffer, RECORD_SIZE, recordno * RECORD_SIZE) == -1) {
        perror("pread");
        close(fd);
        return 1;
    }

    printf("Read record %d: %s\n", recordno, read_buffer);

    unlock_record(fd, recordno); // Release read lock

    // Modify a record (let's say record number 0)
    recordno = 0;
    const char *new_data = "Modified Record 1";

    lock_record(fd, recordno, F_WRLCK); // Acquire write lock

    if (pwrite(fd, new_data, strlen(new_data), recordno * RECORD_SIZE) == -1) {
        perror("pwrite");
        close(fd);
        return 1;
    }

    printf("Modified record %d\n", recordno);

    unlock_record(fd, recordno); // Release write lock

    close(fd);
    return 0;
}
