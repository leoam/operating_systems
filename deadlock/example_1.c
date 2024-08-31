#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t resourceA;
pthread_mutex_t resourceB;

void* thread1_func(void* arg) {
    // Thread 1 locks resourceA
    pthread_mutex_lock(&resourceA);
    printf("Thread 1: locked resourceA\n");

    // Simulate some work
    sleep(1);

    // Thread 1 tries to lock resourceB
    pthread_mutex_lock(&resourceB);
    printf("Thread 1: locked resourceB\n");

    // Unlock the resources
    pthread_mutex_unlock(&resourceB);
    pthread_mutex_unlock(&resourceA);

    return NULL;
}

void* thread2_func(void* arg) {
    // Thread 2 locks resourceB
    pthread_mutex_lock(&resourceB);
    printf("Thread 2: locked resourceB\n");

    // Simulate some work
    sleep(1);

    // Thread 2 tries to lock resourceA
    pthread_mutex_lock(&resourceA);
    printf("Thread 2: locked resourceA\n");

    // Unlock the resources
    pthread_mutex_unlock(&resourceA);
    pthread_mutex_unlock(&resourceB);

    return NULL;
}

int main() {
    pthread_t thread1, thread2;

    // Initialize the mutexes
    pthread_mutex_init(&resourceA, NULL);
    pthread_mutex_init(&resourceB, NULL);

    // Create the threads
    pthread_create(&thread1, NULL, thread1_func, NULL);
    pthread_create(&thread2, NULL, thread2_func, NULL);

    // Wait for the threads to finish
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    // Destroy the mutexes
    pthread_mutex_destroy(&resourceA);
    pthread_mutex_destroy(&resourceB);

    return 0;
}

/*
 * In this program, resourceA and resourceB are the resources that the threads are trying to lock.
 * thread1 locks resourceA first and then tries to lock resourceB, while thread2 locks resourceB first and
 * then tries to lock resourceA. This can lead to a deadlock if both threads are blocked waiting for the
 * other to release the resource they need.
 */

