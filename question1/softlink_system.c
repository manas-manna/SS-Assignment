#include <stdio.h>
#include <unistd.h>

int main() {
    

    if (symlink("question1.txt", "question1_soft.txt") == -1) { //symlink will return -1 if error otherwise 0
        perror("symlink error"); // Print an error message
        return 1; // Indicate an error occurred
    }

    printf("Soft link created successfully!\n");
    return 0;
}
