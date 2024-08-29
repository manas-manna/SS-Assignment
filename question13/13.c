#include <sys/types.h>
#include <sys/time.h>
#include <err.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int
main(void)
{
    int value = 0;
    struct timeval tmo;
    fd_set readfds;

    printf("Enter anything: ");
    fflush(stdout);

    /* wait only 5 seconds for user input */
    FD_ZERO(&readfds);
    FD_SET(0, &readfds);
    tmo.tv_sec = 5;
    tmo.tv_usec = 0;

    switch (select(1, &readfds, NULL, NULL, &tmo)) {
    case -1:
        err(1, "select");
        break;
    case 0:
	fflush(stdout);
        printf("User dont give input\n");
	return (1);
    default:
	printf("User gave input\n");
    }

    scanf("%d", &value);
    return (0);
}

