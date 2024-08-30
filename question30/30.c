#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <string.h>

int main() {
    pid_t pid, sid;


    // Fork off the parent process
    pid = fork();
    if (pid < 0) {
        exit(EXIT_FAILURE);
    }
    if (pid > 0) {
        exit(EXIT_SUCCESS);
    }

    // Create a new session
    sid = setsid();
    if (sid < 0) {
        exit(EXIT_FAILURE);
    }

    // Change the working directory to root
    if ((chdir("/")) < 0) {
        exit(EXIT_FAILURE);
    }

    // Close standard file descriptors
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    // The script to be executed 
    const char *script_path = "/home/manas/SS\\ Assignment/question30/printscript.sh";

    // Get current time in IST
    time_t current_time_raw = time(NULL);
    struct tm current_time;
    localtime_r(&current_time_raw, &current_time);

    // Set target time based on current time (10 minutes ahead)
    struct tm target_time = current_time; 
    target_time.tm_min += 1;
    if (target_time.tm_min >= 60) {
        target_time.tm_min -= 60;
        target_time.tm_hour++;
        if (target_time.tm_hour >= 24) {
            target_time.tm_hour = 0; 
            target_time.tm_mday++;  // Handle day rollover (simplified)
        }
    }

    // Convert target_time to timestamp
    time_t target_timestamp = mktime(&target_time);
    if (target_timestamp == -1) {
        perror("Error in mktime");
        return 1; 
    }

    FILE *log_file = fopen("/home/manas/my_daemon.log", "a"); 
    if (log_file == NULL) {
        perror("Error opening log file");
        return 1;
    }

    fprintf(log_file, "Target timestamp: %ld\n", target_timestamp);
    fprintf(log_file, "Current timestamp: %ld\n", current_time_raw);

    while (1) {
        time_t current_time = time(NULL);

        if (current_time >= target_timestamp) {
            fprintf(log_file, "Executing script at current time: %ld\n", current_time);

            char command[500];
            snprintf(command, sizeof(command), "%s >> /home/manas/SS\\ Assignment/question30/script_output.txt 2>&1", script_path);
            if (system(command) == -1) {
                perror("Error executing script"); 
            }
            break; 
        }

        sleep(1); 
    }

    fclose(log_file);
    return 0;
}
