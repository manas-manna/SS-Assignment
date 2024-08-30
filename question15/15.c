#include <stdio.h>
extern char **environ; //this line telling use environ  which is declared in linux
//#include <unistd.h>  // This header has environ

int main() {
    int i = 0;
	printf("Environment variables of current user are: \n");
    while (environ[i] != NULL) {
        printf("%s\n", environ[i]);
        i++;
    }

    return 0;
}
