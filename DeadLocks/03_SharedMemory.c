#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define SHM_SIZE 1024

int main() {
    HANDLE hMapFile;
    LPVOID shared_memory;
    PROCESS_INFORMATION pi;
    STARTUPINFO si;

    // Create file mapping
    hMapFile = CreateFileMapping(
        INVALID_HANDLE_VALUE,    // use paging file
        NULL,                    // default security
        PAGE_READWRITE,          // read/write access
        0,                       // maximum object size (high-order DWORD)
        SHM_SIZE,               // maximum object size (low-order DWORD)
        "SharedMemory");         // name of mapping object

    if (hMapFile == NULL) {
        printf("Could not create file mapping object (%d).\n", GetLastError());
        return 1;
    }

    // Map view of file
    shared_memory = MapViewOfFile(hMapFile, FILE_MAP_ALL_ACCESS, 0, 0, SHM_SIZE);
    if (shared_memory == NULL) {
        printf("Could not map view of file (%d).\n", GetLastError());
        CloseHandle(hMapFile);
        return 1;
    }

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    // Create child process
    if (!CreateProcess(NULL, "child.exe", NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
        printf("CreateProcess failed (%d).\n", GetLastError());
        return 1;
    }

    // Wait for child process to finish
    WaitForSingleObject(pi.hProcess, INFINITE);

    printf("Parent process reading from shared memory: %s\n", (char*)shared_memory);

    // Cleanup
    UnmapViewOfFile(shared_memory);
    CloseHandle(hMapFile);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return 0;
}