#include <stdio.h>
#include <unistd.h>
#include <stdint.h> // For uint64_t

int main() {
    uint64_t start, end;

    // Get the starting timestamp
    start =__builtin_ia32_rdtsc();

    // Call the getpid system call
    getpid();

    // Get the ending timestamp
    end =__builtin_ia32_rdtsc();

    // Calculate and print the elapsed time in CPU cycles
    uint64_t elapsed_cycles = end - start;
    printf("Time taken to execute getpid: %lu CPU cycles\n", elapsed_cycles);

    return 0;
}
