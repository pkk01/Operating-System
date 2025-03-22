
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 5

pthread_mutex_t mutex;
int counter = 0;

void* threadFunction(void* arg) {
    int thread_id = *((int*)arg);
    free(arg);

    pthread_mutex_lock(&mutex);
    counter++;
    printf("Thread %d: Counter value: %d\n", thread_id, counter);
    pthread_mutex_unlock(&mutex);

    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
if (pthread_mutex_init(&mutex, NULL) != 0) {
    perror("Mutex initialization failed");
    return 1;
}

    for (int i = 0; i < NUM_THREADS; i++) {
        int* thread_id = malloc(sizeof(int));
if (thread_id == NULL) {
    perror("Failed to allocate memory for thread ID");
    return 1;
}
        *thread_id = i;
        if (pthread_create(&threads[i], NULL, threadFunction, thread_id) != 0) {
    perror("Failed to create thread");
    free(thread_id); // Free allocated memory on failure
    return 1;
}
            perror("Failed to create thread");
            return 1;
        }
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    return 0;
}
