#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

void* threadFunction(void* arg) {
    int id = *(int*)arg;
    printf("Thread %d: Started\n", id);

    sleep(1);  // Simulate work

    printf("Thread %d: Exiting using pthread_exit()\n", id);
    pthread_exit((void*)(long)(id * 10)); // Return some value
}

int main() {
    pthread_t t1, t2;
    int id1 = 1, id2 = 2;
    void* retval1;
    void* retval2;

    // (i) Create threads
    pthread_create(&t1, NULL, threadFunction, &id1);
    pthread_create(&t2, NULL, threadFunction, &id2);

    // (iii) Check if threads are equal
    if (pthread_equal(t1, t2))
        printf("Threads t1 and t2 are equal\n");
    else
        printf("Threads t1 and t2 are NOT equal\n");

    // (ii) Join threads
    pthread_join(t1, &retval1);
    pthread_join(t2, &retval2);

    printf("Returned value from Thread 1: %ld\n", (long)retval1);
    printf("Returned value from Thread 2: %ld\n", (long)retval2);

    printf("Main thread exiting.\n");
    return 0;
}

