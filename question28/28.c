#include <stdio.h>
#include <sched.h>

int main() {
    int max_priority = sched_get_priority_max(SCHED_FIFO);
    int min_priority = sched_get_priority_min(SCHED_FIFO);

    if (max_priority == -1 || min_priority == -1) {
        perror("Error getting priorities");
        return 1;
    }

    printf("Maximum real-time priority (SCHED_FIFO): %d\n", max_priority);
    printf("Minimum real-time priority (SCHED_FIFO): %d\n", min_priority);

    return 0;
}
