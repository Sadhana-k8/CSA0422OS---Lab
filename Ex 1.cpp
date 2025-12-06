#include <windows.h>
#include <stdio.h>

int main() {
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    printf("Parent Process:\n");
    printf("Parent PID: %lu\n", GetCurrentProcessId());

    // Create a new process (child)
    if (!CreateProcess(
        NULL,               // No module name
        "notepad.exe",      // Command to run child process
        NULL,
        NULL,
        FALSE,
        0,
        NULL,
        NULL,
        &si,
        &pi
    )) {
        printf("Process Creation Failed! Error: %lu\n", GetLastError());
        return 1;
    }

    printf("Child Process created!\n");
    printf("Child PID: %lu\n", pi.dwProcessId);

    // Close process handles
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return 0;
}

