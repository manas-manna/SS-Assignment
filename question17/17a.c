#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    const char *filename = "tickets.txt"; // File to store the ticket number
    int fd;

    // Open or create the file in write-only mode, truncating it if it exists
    fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    int initial_ticket_number = 1000; // Starting ticket number

    // Write the initial ticket number to the file
    if (dprintf(fd, "%d\n", initial_ticket_number) < 0) { 
        perror("dprintf");
        close(fd);
        return 1;
    }

    close(fd);
    printf("Ticket counter initialized with ticket number: %d\n", initial_ticket_number);
    return 0;
}
