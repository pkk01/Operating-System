#include <stdio.h>
#include <windows.h>
#include <process.h>

#define N 5 // Number of philosophers

HANDLE mutex;
HANDLE S[N];

enum { THINKING, HUNGRY, EATING } state[N];
int phil[N] = {0, 1, 2, 3, 4};

void test(int);
void take_fork(int);
void put_fork(int);
unsigned __stdcall philosopher(void *num);

int main() {
    int i;
    HANDLE thread_id[N];

    mutex = CreateSemaphore(NULL, 1, 1, NULL);
    for (i = 0; i < N; i++)
        S[i] = CreateSemaphore(NULL, 0, 1, NULL);

    for (i = 0; i < N; i++) {
        thread_id[i] = (HANDLE)_beginthreadex(NULL, 0, philosopher, &phil[i], 0, NULL);
        printf("Philosopher %d is thinking\n", i + 1);
    }

    WaitForMultipleObjects(N, thread_id, TRUE, INFINITE);

    // Cleanup
    CloseHandle(mutex);
    for (i = 0; i < N; i++)
        CloseHandle(S[i]);

    return 0;
}

unsigned __stdcall philosopher(void *num) {
    int i = *(int *)num;
    while (1) {
        Sleep(1000);
        take_fork(i);
        Sleep(1000);
        put_fork(i);
    }
    return 0;
}

void take_fork(int phil_num) {
    WaitForSingleObject(mutex, INFINITE);
    state[phil_num] = HUNGRY;
    printf("Philosopher %d is hungry\n", phil_num + 1);
    test(phil_num);
    ReleaseSemaphore(mutex, 1, NULL);
    WaitForSingleObject(S[phil_num], INFINITE);
}

void put_fork(int phil_num) {
    WaitForSingleObject(mutex, INFINITE);
    state[phil_num] = THINKING;
    printf("Philosopher %d is putting fork %d and %d down\n", phil_num + 1, phil_num + 1, (phil_num + 1) % N + 1);
    printf("Philosopher %d is thinking\n", phil_num + 1);
    test((phil_num + 4) % N);
    test((phil_num + 1) % N);
    ReleaseSemaphore(mutex, 1, NULL);
}

void test(int phil_num) {
    if (state[phil_num] == HUNGRY &&
        state[(phil_num + 4) % N] != EATING &&
        state[(phil_num + 1) % N] != EATING) {
        state[phil_num] = EATING;
        printf("Philosopher %d is taking fork %d and %d\n", phil_num + 1, phil_num + 1, (phil_num + 1) % N + 1);
        printf("Philosopher %d is eating\n", phil_num + 1);
        ReleaseSemaphore(S[phil_num], 1, NULL);
    }
}
