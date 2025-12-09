#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 5  // Number of philosophers
#define LEFT (phnum + 4) % N
#define RIGHT (phnum + 1) % N

sem_t mutex;            // For critical section
sem_t S[N];             // One semaphore per philosopher

enum { THINKING, HUNGRY, EATING } state[N];
int phil[N] = {0, 1, 2, 3, 4};

void test(int phnum) {
    if (state[phnum] == HUNGRY &&
        state[LEFT] != EATING &&
        state[RIGHT] != EATING) {

        state[phnum] = EATING;
        sleep(1);

        printf("Philosopher %d takes fork %d and %d\n",
               phnum, LEFT, phnum);

        printf("Philosopher %d is Eating\n", phnum);

        sem_post(&S[phnum]);
    }
}

void take_fork(int phnum) {
    sem_wait(&mutex);

    state[phnum] = HUNGRY;
    printf("Philosopher %d is Hungry\n", phnum);

    test(phnum);

    sem_post(&mutex);

    sem_wait(&S[phnum]);
    sleep(1);
}

void put_fork(int phnum) {
    sem_wait(&mutex);

    state[phnum] = THINKING;
    printf("Philosopher %d puts fork %d and %d down\n",
           phnum, LEFT, phnum);

    printf("Philosopher %d is Thinking\n", phnum);

    test(LEFT);
    test(RIGHT);

    sem_post(&mutex);
}

void* philosopher(void* num) {
    while (1) {
        int* i = num;
        sleep(1);
        take_fork(*i);
        sleep(2);
        put_fork(*i);
    }
}

int main() {
    int i;
    pthread_t thread_id[N];

    sem_init(&mutex, 0, 1);

    for (i = 0; i < N; i++)
        sem_init(&S[i], 0, 0);

    for (i = 0; i < N; i++)
        pthread_create(&thread_id[i], NULL,
                       philosopher, &phil[i]);

    for (i = 0; i < N; i++)
        pthread_join(thread_id[i], NULL);

    return 0;
}

