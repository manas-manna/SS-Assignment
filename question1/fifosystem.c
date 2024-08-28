
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>

int main() {
    
    if (mknod("sys_fifo", S_IFIFO | 0666, 0) == -1) {   //can also use  if (mkfifo(fifo_name, 0666) == -1)
        perror("mknod"); // Print an error message if mknod fails
        return 1;
    }

    printf("FIFO created successfully!\n");
    return 0; 
}
