#include <stdio.h>
#include <unistd.h>

int main() {
    

    if (link("question1hardlink.txt", "question1hardlink_link.txt") == -1) { //symlink will return -1 if error otherwise 0
        perror("symlink error"); // Print an error message
        return 1; // Indicate an error occurred
    }

    printf("Hardlink created successfully!\n");
    return 0;
}
