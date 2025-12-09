#include <stdio.h>
#include <pthread.h>

int counter = 0;               // Shared resource
pthread_mutex_t lock;          // Mutex lock

void* increment(void* arg) {
    for (int i = 0; i < 5; i++) {

        pthread_mutex_lock(&lock);     // Acquire lock
        counter++;
        printf("Thread %ld incremented counter to %d\n", (long)arg, counter);
        pthread_mutex_unlock(&lock);   // Release lock
    }
    return NULL;
}

int main() {
    pthread_t t1, t2;

    // Initialize mutex
    pthread_mutex_init(&lock, NULL);

    // Create threads
    pthread_create(&t1, NULL, increment, (void*)1);
    pthread_create(&t2, NULL, increment, (void*)2);

    // Wait for threads
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    // Destroy mutex
    pthread_mutex_destroy(&lock);

    printf("\nFinal counter value = %d\n", counter);

    return 0;
}


