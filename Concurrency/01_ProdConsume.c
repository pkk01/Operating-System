#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define BUFFER_SIZE 10

int buffer[BUFFER_SIZE];
int count = 0;

CRITICAL_SECTION cs;
HANDLE empty, full;

DWORD WINAPI producer(LPVOID param) {
    int item;
    while (1) {
        item = rand() % 100; // Produce an item

        WaitForSingleObject(empty, INFINITE);
        EnterCriticalSection(&cs);

        buffer[count++] = item;
        printf("Producer produced: %d\n", item);

        LeaveCriticalSection(&cs);
        ReleaseSemaphore(full, 1, NULL);

        Sleep(500); // Slow down to observe output
    }
    return 0;
}

DWORD WINAPI consumer(LPVOID param) {
    int item;
    while (1) {
        WaitForSingleObject(full, INFINITE);
        EnterCriticalSection(&cs);

        item = buffer[--count];
        printf("Consumer consumed: %d\n", item);

        LeaveCriticalSection(&cs);
        ReleaseSemaphore(empty, 1, NULL);

        Sleep(500); // Slow down to observe output
    }
    return 0;
}

int main() {
    HANDLE producerThread, consumerThread;

    InitializeCriticalSection(&cs);
    empty = CreateSemaphore(NULL, BUFFER_SIZE, BUFFER_SIZE, NULL);
    full = CreateSemaphore(NULL, 0, BUFFER_SIZE, NULL);

    producerThread = CreateThread(NULL, 0, producer, NULL, 0, NULL);
    consumerThread = CreateThread(NULL, 0, consumer, NULL, 0, NULL);

    WaitForSingleObject(producerThread, INFINITE);
    WaitForSingleObject(consumerThread, INFINITE);

    CloseHandle(producerThread);
    CloseHandle(consumerThread);

    DeleteCriticalSection(&cs);
    CloseHandle(empty);
    CloseHandle(full);

    return 0;
}
