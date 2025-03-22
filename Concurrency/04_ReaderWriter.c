#include <windows.h>
#include <stdio.h>
#include <stdint.h>  // <-- Add this for intptr_t

CRITICAL_SECTION readCountMutex;
HANDLE resourceAccess;
int readCount = 0;

DWORD WINAPI Reader(LPVOID param) {
    int id = (int)(intptr_t)param;
    while (1) {
        EnterCriticalSection(&readCountMutex);
        readCount++;
        if (readCount == 1) {
            WaitForSingleObject(resourceAccess, INFINITE);
        }
        LeaveCriticalSection(&readCountMutex);

        printf("Reader %d is reading...\n", id);
        Sleep(1000);
        printf("Reader %d finished reading.\n", id);

        EnterCriticalSection(&readCountMutex);
        readCount--;
        if (readCount == 0) {
            ReleaseSemaphore(resourceAccess, 1, NULL);
        }
        LeaveCriticalSection(&readCountMutex);

        Sleep(rand() % 3000);
    }
    return 0;
}

DWORD WINAPI Writer(LPVOID param) {
    int id = (int)(intptr_t)param;
    while (1) {
        WaitForSingleObject(resourceAccess, INFINITE);

        printf("Writer %d is writing...\n", id);
        Sleep(2000);
        printf("Writer %d finished writing.\n", id);

        ReleaseSemaphore(resourceAccess, 1, NULL);
        Sleep(rand() % 4000);
    }
    return 0;
}

int main() {
    InitializeCriticalSection(&readCountMutex);
    resourceAccess = CreateSemaphore(NULL, 1, 1, NULL);

    HANDLE readers[3], writers[2];
    for (int i = 0; i < 3; i++) {
        readers[i] = CreateThread(NULL, 0, Reader, (LPVOID)(intptr_t)(i + 1), 0, NULL);
    }
    for (int i = 0; i < 2; i++) {
        writers[i] = CreateThread(NULL, 0, Writer, (LPVOID)(intptr_t)(i + 1), 0, NULL);
    }

    WaitForMultipleObjects(3, readers, TRUE, INFINITE);
    WaitForMultipleObjects(2, writers, TRUE, INFINITE);

    DeleteCriticalSection(&readCountMutex);
    CloseHandle(resourceAccess);

    return 0;
}
