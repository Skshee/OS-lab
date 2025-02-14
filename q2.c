#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_READERS 5
#define NUM_WRITERS 2

sem_t mutex; // Mutex for protecting the read_count
sem_t write_lock; // Semaphore for writers
int read_count = 0; // Number of active readers

void* reader(void* id) {
    int reader_id = *(int*)id;

    for (int i = 0; i < 3; i++) {
        // Start reading
        sem_wait(&mutex); // Lock the mutex
        read_count++;
        if (read_count == 1) {
            sem_wait(&write_lock); // First reader locks the writer
        }
        sem_post(&mutex); // Unlock the mutex

        // Reading section
        printf("Reader %d is reading.\n", reader_id);
        sleep(1); // Simulate reading time

        // End reading
        sem_wait(&mutex); // Lock the mutex
        read_count--;
        if (read_count == 0) {
            sem_post(&write_lock); // Last reader unlocks the writer
        }
        sem_post(&mutex); // Unlock the mutex

        sleep(1); // Simulate time between reads
    }
    return NULL;
}

void* writer(void* id) {
    int writer_id = *(int*)id;

    for (int i = 0; i < 3; i++) {
        // Start writing
        sem_wait(&write_lock); // Lock the writer

        // Writing section
        printf("Writer %d is writing.\n", writer_id);
        sleep(2); // Simulate writing time

        // End writing
        sem_post(&write_lock); // Unlock the writer

        sleep(1); // Simulate time between writes
    }
    return NULL;
}

int main() {
    pthread_t readers[NUM_READERS], writers[NUM_WRITERS];
    int reader_ids[NUM_READERS], writer_ids[NUM_WRITERS];

    // Initialize semaphores
    sem_init(&mutex, 0, 1); // Binary semaphore for read_count
    sem_init(&write_lock, 0, 1); // Binary semaphore for writers

    // Create reader threads
    for (int i = 0; i < NUM_READERS; i++) {
        reader_ids[i] = i + 1;
        pthread_create(&readers[i], NULL, reader, &reader_ids[i]);
    }

    // Create writer threads
    for (int i = 0; i < NUM_WRITERS; i++) {
        writer_ids[i] = i + 1;
        pthread_create(&writers[i], NULL, writer, &writer_ids[i]);
    }

    // Wait for all threads to finish
    for (int i = 0; i < NUM_READERS; i++) {
        pthread_join(readers[i], NULL);
    }
    for (int i = 0; i < NUM_WRITERS; i++) {
        pthread_join(writers[i], NULL);
    }

    // Clean up
    sem_destroy(&mutex);
    sem_destroy(&write_lock);

    return 0;
}
