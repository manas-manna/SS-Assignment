#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {

    char *program_path = "./26a";


    int a, b;
    printf("Enter two numbers: ");
    scanf("%d %d", &a, &b);

    char command[100];
    snprintf(command, sizeof(command), "%s %d %d", program_path, a, b);

    // Execute the command using system
    int result = system(command);

    if (result == -1) {
        perror("Error executing command");
        return 1;
    }

    return 0;
}
