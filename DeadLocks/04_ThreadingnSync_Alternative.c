#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 5

int counter = 0;

void simulateThreadFunction(int thread_id) {
    counter++;
    printf("Thread %d: Counter value: %d\n", thread_id, counter);
}

int main() {
    for (int i = 0; i < NUM_THREADS; i++) {
        simulateThreadFunction(i);
    }

    return 0;
}
