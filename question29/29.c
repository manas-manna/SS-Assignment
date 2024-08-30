#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sched.h>

int main() {
    pid_t pid = getpid(); // Get the PID of the current process

    // Get the current scheduling policy and priority
    struct sched_param current_param;
    int current_policy = sched_getscheduler(pid);

    if (current_policy == -1) {
        perror("Error getting current scheduling policy");
        return 1;
    }

    if (sched_getparam(pid, &current_param) == -1) {
        perror("Error getting current scheduling parameters");
        return 1;
    }

    printf("Current scheduling policy: ");
    switch (current_policy) {
        case SCHED_OTHER:
            printf("SCHED_OTHER (normal)\n");
            break;
        case SCHED_FIFO:
            printf("SCHED_FIFO (real-time, first-in-first-out)\n");
            break;
        case SCHED_RR:
            printf("SCHED_RR (real-time, round-robin)\n");
            break;
        default:
            printf("Unknown policy (%d)\n", current_policy);
    }
    printf("Current priority: %d\n", current_param.sched_priority);

    // Modify the scheduling policy (example: change to SCHED_FIFO)
    struct sched_param new_param;
    new_param.sched_priority = 50; // Set a real-time priority (needs to be within allowed range)
    int new_policy = SCHED_FIFO;

    if (sched_setscheduler(pid, new_policy, &new_param) == -1) {
        perror("Error setting new scheduling policy");
        return 1; 
    }

    printf("Scheduling policy changed to SCHED_FIFO with priority 50\n");

    return 0;
}
