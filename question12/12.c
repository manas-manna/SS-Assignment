#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd, flags;

    fd = open("text1.txt", O_RDONLY | O_RDWR);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    // Getting the file status flags using fcntl()
    flags = fcntl(fd, F_GETFL);
    if (flags == -1) {
        perror("fcntl");
        close(fd);
        return 1;
    }

    printf("File opening mode:\n");
    //flags contains a bitmask where each bit represents a mode so we are performing &
    //here "==" will not work bcz == compares two values.but here flag represents multiple values

    if (flags & O_RDONLY)  printf("  Read-only\n");
    if (flags & O_WRONLY)  printf("  Write-only)\n");
    if (flags & O_RDWR)    printf("  Read-write\n");
    if (flags & O_APPEND)  printf("  Append\n");
    if (flags & O_CREAT)   printf("  Create if doesn't exist\n");
    if (flags & O_TRUNC)   printf("  Truncate\n");
    if (flags & O_EXCL)    printf("  Exclusive creation\n");
    

    close(fd);
    return 0;
}
