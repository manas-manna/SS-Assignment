#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
       fprintf(stderr, "Usage: %s <number1> <number2>\n", argv[0]);
        return 1;
    }

    int a = atoi(argv[1]);
    int b = atoi(argv[2]);
    int sum = a + b;

    printf("Printing Sum of %d and %d from program 26a is: %d\n", a, b, sum);
    return 0;
}
