#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd, fd_dup, fd_dup2, fd_fcntl;

    // Opened the file in append mode,create if it doesn't exist
    fd = open("text1.txt", O_RDWR | O_CREAT | O_APPEND, 0644);  //0_CREAT is optional.If file is already created then its not required

    if (fd == -1) {
        perror("open");
        return 1; 
    }

    // Duplicate using dup()
    fd_dup = dup(fd);
    if (fd_dup == -1) {
        perror("dup");
        close(fd);
        return 1;
    }

    // Duplicate using dup2()
    fd_dup2 = 10; // Choose a desired file descriptor number
    if (dup2(fd, fd_dup2) == -1) {    //will close all opened files if any error coming
        perror("dup2");
        close(fd);
        close(fd_dup);
        return 1;
    }

    // Duplicate using fcntl()
    fd_fcntl = fcntl(fd, F_DUPFD, 10); // Start searching for an available fd from 10 onwards
    if (fd_fcntl == -1) {
        perror("fcntl");
        close(fd);
        close(fd_dup);
        close(fd_dup2);
        return 1;
    }

    // Append using the original and duplicated file descriptors
    const char *data1 = "Appended using original fd\n";
    const char *data2 = "Appended using dup fd\n";
    const char *data3 = "Appended using dup2 fd\n";
    const char *data4 = "Appended using fcntl fd\n";

    write(fd, data1, strlen(data1));
    write(fd_dup, data2, strlen(data2));
    write(fd_dup2, data3, strlen(data3));
    write(fd_fcntl, data4, strlen(data4));

    // Close all file descriptors
    close(fd);
    close(fd_dup);
    close(fd_dup2);
    close(fd_fcntl);

    // checking file updating or not
    system("cat text1.txt");

    return 0;
}

