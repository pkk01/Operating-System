#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define NUM_THREADS 5

CRITICAL_SECTION cs;
int counter = 0;

DWORD WINAPI threadFunction(LPVOID arg) {
    int thread_id = *((int*)arg);
    free(arg);

    EnterCriticalSection(&cs);
    counter++;
    printf("Thread %d: Counter value: %d\n", thread_id, counter);
    LeaveCriticalSection(&cs);

    return 0;
}

int main() {
    HANDLE threads[NUM_THREADS];
    InitializeCriticalSection(&cs);

    for (int i = 0; i < NUM_THREADS; i++) {
        int* thread_id = malloc(sizeof(int));
        if (thread_id == NULL) {
            printf("Failed to allocate memory\n");
            return 1;
        }
        *thread_id = i;
        threads[i] = CreateThread(NULL, 0, threadFunction, thread_id, 0, NULL);
        if (threads[i] == NULL) {
            printf("Failed to create thread\n");
            free(thread_id);
            return 1;
        }
    }

    WaitForMultipleObjects(NUM_THREADS, threads, TRUE, INFINITE);

    for (int i = 0; i < NUM_THREADS; i++) {
        CloseHandle(threads[i]);
    }

    DeleteCriticalSection(&cs);

    printf("Final counter value: %d\n", counter);
    return 0;
}
