#include <windows.h>
#include <stdio.h>

#define CHAIRS 3

HANDLE customers; 
HANDLE barber;    
CRITICAL_SECTION mutex;
int waiting = 0;

DWORD WINAPI Barber(LPVOID param) {
    while (1) {
        WaitForSingleObject(customers, INFINITE);
        EnterCriticalSection(&mutex);
        waiting--;
        ReleaseSemaphore(barber, 1, NULL);
        LeaveCriticalSection(&mutex);

        printf("Barber is cutting hair.\n");
        Sleep(2000); 
        printf("Barber finished cutting hair.\n");
    }
    return 0;
}

DWORD WINAPI Customer(LPVOID param) {
    EnterCriticalSection(&mutex);
    if (waiting < CHAIRS) {
        waiting++;
        printf("Customer arrived. Waiting chairs occupied: %d\n", waiting);
        ReleaseSemaphore(customers, 1, NULL);
        LeaveCriticalSection(&mutex);
        WaitForSingleObject(barber, INFINITE);
        printf("Customer is getting a haircut.\n");
    } else {
        printf("No chairs available. Customer left.\n");
        LeaveCriticalSection(&mutex);
    }
    return 0;
}

int main() {
    HANDLE barberThread, customerThread;
    customers = CreateSemaphore(NULL, 0, CHAIRS, NULL);
    barber = CreateSemaphore(NULL, 0, 1, NULL);
    InitializeCriticalSection(&mutex);

    barberThread = CreateThread(NULL, 0, Barber, NULL, 0, NULL);

    while (1) {
        Sleep(rand() % 3000);
        customerThread = CreateThread(NULL, 0, Customer, NULL, 0, NULL);
        CloseHandle(customerThread);
    }

    DeleteCriticalSection(&mutex);
    CloseHandle(customers);
    CloseHandle(barber);
    CloseHandle(barberThread);

    return 0;
}
