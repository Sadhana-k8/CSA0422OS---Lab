#include <windows.h>
#include <stdio.h>

// Thread function
DWORD WINAPI threadFunction(LPVOID lpParam) {
    char* message = (char*)lpParam;

    for (int i = 0; i < 5; i++) {
        printf("%s - iteration %d\n", message, i + 1);
        Sleep(500); // sleep 0.5 sec
    }

    return 0;
}

int main() {
    HANDLE thread1, thread2;

    // Create two threads
    thread1 = CreateThread(
        NULL, 0, threadFunction, "Thread 1", 0, NULL);

    thread2 = CreateThread(
        NULL, 0, threadFunction, "Thread 2", 0, NULL);

    // Wait for both threads to finish
    WaitForSingleObject(thread1, INFINITE);
    WaitForSingleObject(thread2, INFINITE);

    // Close thread handles
    CloseHandle(thread1);
    CloseHandle(thread2);

    printf("Both threads have finished execution.\n");

    return 0;
}

