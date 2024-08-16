#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

// Example 3 - Program that will create different threads

#define NUM_THREADS 5

void* thread_function(void* arg) {
    long thread_id = (long)arg;
    printf("Thread ID: %ld\n", thread_id);

    while (1) {
        // Infinite loop
        sleep(1); // Wait for 1 second to avoid CPU overload
    }

    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    pid_t process_id = getpid(); // Get the process ID of the main thread
    printf("Main thread process ID: %d\n", process_id);

    for (long i = 0; i < NUM_THREADS; i++) {
        int result = pthread_create(&threads[i], NULL, thread_function, (void*)i);
        if (result != 0) {
            perror("pthread_create");
            return 1;
        }
    }

    // Main thread also enters an infinite loop
    while (1) {
        sleep(1);
    }

    return 0;
}

