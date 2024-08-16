#include <stdio.h>
#include <unistd.h>

// Example 1. This program will print the running pid and wait until you will it
int main() {
    pid_t process_id = getpid(); // Get the process ID
    printf("The process ID is: %d\n", process_id);

    while (1) {
        // Infinite loop
        sleep(1); // Wait for 1 second to avoid CPU overload
    }

    return 0;
}

