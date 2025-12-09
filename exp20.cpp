#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t rw_mutex;      // Controls access to the shared resource
sem_t mutex;         // Controls access to read_count
int read_count = 0;  // Number of active readers

void* reader(void* p) {
    int id = (long)p;

    sem_wait(&mutex);
    read_count++;
    if (read_count == 1)
        sem_wait(&rw_mutex);   // First reader locks writers
    sem_post(&mutex);

    printf("Reader %d is reading...\n", id);
    sleep(1);

    sem_wait(&mutex);
    read_count--;
    if (read_count == 0)
        sem_post(&rw_mutex);   // Last reader releases writers
    sem_post(&mutex);

    printf("Reader %d finished reading.\n", id);
    return NULL;
}

void* writer(void* p) {
    int id = (long)p;

    sem_wait(&rw_mutex);     // Writer gets exclusive access
    printf("Writer %d is writing...\n", id);
    sleep(1);
    printf("Writer %d finished writing.\n", id);
    sem_post(&rw_mutex);

    return NULL;
}

int main() {
    pthread_t r1, r2, r3, w1, w2;

    sem_init(&rw_mutex, 0, 1);
    sem_init(&mutex, 0, 1);

    pthread_create(&r1, NULL, reader, (void*)1);
    pthread_create(&w1, NULL, writer, (void*)1);
    pthread_create(&r2, NULL, reader, (void*)2);
    pthread_create(&w2, NULL, writer, (void*)2);
    pthread_create(&r3, NULL, reader, (void*)3);

    pthread_join(r1, NULL);
    pthread_join(w1, NULL);
    pthread_join(r2, NULL);
    pthread_join(w2, NULL);
    pthread_join(r3, NULL);

    sem_destroy(&rw_mutex);
    sem_destroy(&mutex);

    return 0;
}

