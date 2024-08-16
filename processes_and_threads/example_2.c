#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

// Example 2 - A single programm that runs on many child processes

int main() {
    pid_t process_id;

    for (int i = 0; i < 5; i++) { // Create 5 child processes
        process_id = fork();

        if (process_id == 0) {
            // This is the child process
            printf("Child process with ID: %d, Parent ID: %d\n", getpid(), getppid());
            while (1) {
                // Infinite loop
                sleep(1); // Wait for 1 second to avoid CPU overload
            }
        } else if (process_id > 0) {
            // This is the parent process
            printf("Parent process with ID: %d created a child with ID: %d\n", getpid(), process_id);
        } else {
            // Error creating the process
            perror("fork");
            return 1;
        }
    }

    // The parent process also enters an infinite loop
    while (1) {
        sleep(1);
    }

    return 0;
}

