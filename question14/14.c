#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

/*************Taking input as argument while executing****************/
/*int main(int argc, char *argv[]) {
    if (argc != 2) {  //number of arguments given(one is program name itself and another is the new filename

        fprintf(stderr, "Usage: %s \n", argv[0]);
        return 1;
    }
    const char *filename = argv[1];
*/
/***************Taking input from stdin*************************/
 int main() {
char filename[256];

    struct stat file_stats;
    //struct stat structure stores various metadata about a  file

printf("Enter the filename: ");
if (scanf("%s", filename) != 1) {
        fprintf(stderr, "Error reading filename from stdin.\n");
        return 1;
    }


    if (lstat(filename, &file_stats) == -1) { // Use lstat to handle symbolic links
       //used lstat instead of stat to handle symbolic links correctly.It gets information about the link itself and not the file it points to
      //if we used stat,then for softlink files it will give information about the ffile it points to and not about the link itself. 
 perror("lstat");
        return 1;
    }

    printf("File Type: ");
   //st_mode of stat structure stores the file type and permissions
    switch (file_stats.st_mode & S_IFMT) { // Mask with S_IFMT(bitmask) to get the file type bits
        case S_IFREG:  printf("Regular file\n");     break;
        case S_IFDIR:  printf("Directory\n");        break;
        case S_IFCHR:  printf("Character device\n");  break;
        case S_IFBLK:  printf("Block device\n");     break;
        case S_IFIFO:
  printf("FIFO (named pipe)\n"); break;
        case S_IFLNK:  printf("Symbolic link\n");     break;

        case S_IFSOCK: printf("Socket\n");           break;
        default:       printf("Unknown file type\n"); break;
    }

    return 0;
}
