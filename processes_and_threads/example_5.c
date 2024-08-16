#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_THREADS 5
#define NUM_INCREMENTS 100000

int shared_variable = 0;
pthread_mutex_t lock;

void* thread_function(void* arg) {
    for (int i = 0; i < NUM_INCREMENTS; i++) {
        pthread_mutex_lock(&lock); // Lock the mutex
        shared_variable++; // Increment the shared variable
        pthread_mutex_unlock(&lock); // Unlock the mutex
    }
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];

    // Initialize the mutex
    if (pthread_mutex_init(&lock, NULL) != 0) {
        perror("pthread_mutex_init");
        return 1;
    }

    for (long i = 0; i < NUM_THREADS; i++) {
        int result = pthread_create(&threads[i], NULL, thread_function, NULL);
        if (result != 0) {
            perror("pthread_create");
            return 1;
        }
    }

    for (long i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Destroy the mutex
    pthread_mutex_destroy(&lock);

    // Print the final value of the shared variable
    printf("Final value of shared variable: %d\n", shared_variable);

    return 0;
}

/*
Explanation:
- Shared Variable: `shared_variable` is accessed and modified by multiple threads.
- Mutex: A mutex (`pthread_mutex_t lock`) is used to ensure that only one thread can increment the shared variable at a time, preventing race conditions.
- Lock and Unlock: `pthread_mutex_lock(&lock)` locks the mutex before incrementing the shared variable, and `pthread_mutex_unlock(&lock)` unlocks it after the increment.
- Initialization and Destruction: The mutex is initialized with `pthread_mutex_init(&lock, NULL)` and destroyed with `pthread_mutex_destroy(&lock)` to free resources.
*/

