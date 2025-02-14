#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5
#define NUM_ITEMS 10

int buffer[BUFFER_SIZE];
int in = 0; // Index for the next item to produce
int out = 0; // Index for the next item to consume

sem_t empty; // Semaphore to count empty slots in the buffer
sem_t full;  // Semaphore to count full slots in the buffer
pthread_mutex_t mutex; // Mutex for mutual exclusion

void* producer(void* param) {
    for (int i = 0; i < NUM_ITEMS; i++) {
        // Produce an item
        int item = rand() % 100; // Random item
        sem_wait(&empty); // Decrease the count of empty slots
        pthread_mutex_lock(&mutex); // Lock the buffer

        // Add the item to the buffer
        buffer[in] = item;
        printf("Producer produced: %d at index %d\n", item, in);
        in = (in + 1) % BUFFER_SIZE; // Move to the next index

        pthread_mutex_unlock(&mutex); // Unlock the buffer
        sem_post(&full); // Increase the count of full slots

        sleep(rand() % 2); // Sleep for a random time
    }
    return NULL;
}

void* consumer(void* param) {
    for (int i = 0; i < NUM_ITEMS; i++) {
        sem_wait(&full); // Decrease the count of full slots
        pthread_mutex_lock(&mutex); // Lock the buffer

        // Remove an item from the buffer
        int item = buffer[out];
        printf("Consumer consumed: %d from index %d\n", item, out);
        out = (out + 1) % BUFFER_SIZE; // Move to the next index

        pthread_mutex_unlock(&mutex); // Unlock the buffer
        sem_post(&empty); // Increase the count of empty slots

        sleep(rand() % 2); // Sleep for a random time
    }
    return NULL;
}

int main() {
    pthread_t prod, cons;

    // Initialize semaphores and mutex
    sem_init(&empty, 0, BUFFER_SIZE); // Initially, all slots are empty
    sem_init(&full, 0, 0); // Initially, no slots are full
    pthread_mutex_init(&mutex, NULL);

    // Create producer and consumer threads
    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);

    // Wait for threads to finish
    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    // Clean up
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0;
}
