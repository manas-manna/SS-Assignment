/*
============================================================================
Name : 27.c
Author : Manas Ranjan Manna
Description : Write a program to execute ls -Rl by the following system calls
 a. execl
 b. execlp
 c. execle
 d. execv
 e. execvp
Date: 31th Aug, 2024.
============================================================================
*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h> 

int main() {
    // (a) execl
    // execl("/bin/ls", "ls", "-Rl", NULL); 

    // (b) execlp
    // execlp("ls", "ls", "-Rl", NULL); 

    // (c) execle 
    // char *envp[] = { NULL }; // No additional environment variables
    // execle("/bin/ls", "ls", "-Rl", NULL, envp); 

    // (d) execv
    // char *args[] = {"ls", "-Rl", NULL};
    // execv("/bin/ls", args); 

    // (e) execvp
    char *args[] = {"ls", "-Rl", NULL};
    execvp("ls", args); 

    // exec functions only return on error
    perror("exec failed");
    exit(EXIT_FAILURE);

    return 0; // This line will never be reached
}
