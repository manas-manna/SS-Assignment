#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h> 
#include <stdlib.h>

int main() {
    int current_priority, new_priority, adjustment;
    char command[100];

    // Get the current priority 
   //nice value lies between -20 to 19.Lower is more priority
    errno = 0; 
    current_priority = getpriority(PRIO_PROCESS, 0); 
    if (current_priority == -1 && errno != 0) {
        perror("getpriority");
        return 1;
    }

    printf("Current priority is: %d\n", current_priority);

    // Get the desired adjustment from the user
    printf("Enter the nice value adjustment: ");
    if (scanf("%d", &adjustment) != 1) {
        fprintf(stderr, "Error reading adjustment value.\n");
        return 1;
    }

    // Construct the nice command
    //snprintf(command, 100, "nice -n %d %s", adjustment, "true"); // 'true' is a dummy command bcz nice() needs some command to run
    new_priority = nice(adjustment);
    // Execute the nice command
    //int result = system(command);
    //usleep(100000); // Sleep for 100 milliseconds
    if (new_priority != -1) {
        /* Get the new priority after the nice command
        errno = 0;
        new_priority = getpriority(PRIO_PROCESS, 0);
        if (new_priority == -1 && errno != 0) {
            perror("getpriority (after nice)");
            return 1;
        }
        */

        printf("Priority changed to: %d\n", new_priority);
    } else {
        fprintf(stderr, "Error executing nice command.\n");
        return 1;
    }

    return 0;
}
