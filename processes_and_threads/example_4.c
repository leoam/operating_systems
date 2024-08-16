#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_THREADS 5
#define NUM_INCREMENTS 100000

/*                                                                                                                                        Explanation:                                                                                                                              - Shared Variable: `shared_variable` is accessed and modified by multiple threads without any synchronization mechanism.
- Race Condition: Because the threads increment the shared variable concurrently, the final value of `shared_variable` will likely be less than `NUM_THREADS * NUM_INCREMENTS` due to race conditions.
*/  

int shared_variable = 0;

void* thread_function(void* arg) {
    for (int i = 0; i < NUM_INCREMENTS; i++) {
        shared_variable++; // Increment the shared variable
    }
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];

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

    // Print the final value of the shared variable
    printf("Final value of shared variable: %d\n", shared_variable);

    return 0;
}

