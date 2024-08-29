#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>

int main() {
    const char *filename = "file1.txt"; 
    struct stat file_stats;

    if (stat(filename, &file_stats) == -1) {
        perror("stat");
        return 1;
    }

    printf("File Information for: %s\n", filename);
    printf("-------------------------------------\n");
    printf("Inode: %ld\n", (long) file_stats.st_ino);
    printf("Number of hard links: %ld\n", (long) file_stats.st_nlink);
    printf("UID: %d\n", file_stats.st_uid);
    printf("GID: %d\n", file_stats.st_gid);
    printf("Size: %lld bytes\n", (long long) file_stats.st_size);
    printf("Block size: %ld bytes\n", (long) file_stats.st_blksize);
    printf("Number of blocks: %lld\n", (long long) file_stats.st_blocks);

    // Convert timestamps to human-readable format
    char time_buffer[80];
    strftime(time_buffer, 80, "%Y-%m-%d %H:%M:%S", localtime(&file_stats.st_atime));
    printf("Time of last access: %s\n", time_buffer);

    strftime(time_buffer, 80, "%Y-%m-%d %H:%M:%S", localtime(&file_stats.st_mtime));
    printf("Time of last modification: %s\n", time_buffer);

    strftime(time_buffer, 80, "%Y-%m-%d %H:%M:%S", localtime(&file_stats.st_ctime));
    printf("Time of last change: %s\n", time_buffer);

    return 0;
}
