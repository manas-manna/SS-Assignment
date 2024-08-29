#include <stdio.h>
#include <stdlib.h>  //it has system()

int main() {

    char command[200];  //here the command will get stored
    snprintf(command, 200, "cp %s %s", "text1.txt" , "text2.txt");
    //snprintf is C library function used to format a string as per a given format

    if (system(command) == 0) {  //system() is a C library function used to run a shell command within the C program itself

        printf("File copied successfully using cp\n");

    } else {
        fprintf(stderr, "Error copying file using cp. Check if the files exist and you have permissions.\n");
        return 1; 
    }

    return 0;
}
