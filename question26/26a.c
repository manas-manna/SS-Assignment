#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
       fprintf(stderr, "Usage: %s <number1> <number2>\n", argv[0]);
        return 1;
    }
    //agrv is of string form.We need to convert them to integer.
    int a = atoi(argv[1]);   //atoi stands for ascii to  integer.It converts string to integer
    int b = atoi(argv[2]);
    int sum = a + b;

    printf("Printing Sum of %d and %d from program 26a is: %d\n", a, b, sum);
    return 0;
}
