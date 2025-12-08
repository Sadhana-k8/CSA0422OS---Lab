#include <windows.h>
#include <stdio.h>

int main() {
    HANDLE hMapFile;
    LPCTSTR pBuf;

    // Create shared memory
    hMapFile = CreateFileMapping(
        INVALID_HANDLE_VALUE,   // use paging file
        NULL,                   // default security
        PAGE_READWRITE,         // read/write access
        0,                      // maximum object size (high-order DWORD)
        256,                    // maximum object size (low-order DWORD)
        "MySharedMemory");      // name of mapping object

    if (hMapFile == NULL) {
        printf("Could not create file mapping object (%d).\n", GetLastError());
        return 1;
    }

    pBuf = (LPTSTR) MapViewOfFile(hMapFile,   // handle to map object
                                  FILE_MAP_ALL_ACCESS, // read/write permission
                                  0,
                                  0,
                                  256);

    if (pBuf == NULL) {
        printf("Could not map view of file (%d).\n", GetLastError());
        CloseHandle(hMapFile);
        return 1;
    }

    // --------- User input ------------
    char msg[100];
    printf("Enter message to child: ");
    fgets(msg, sizeof(msg), stdin);

    // Write to shared memory
    memcpy((PVOID)pBuf, msg, strlen(msg) + 1);

    printf("Message written to shared memory.\n");

    // Launch child process
    STARTUPINFO si = { sizeof(si) };
    PROCESS_INFORMATION pi;

    CreateProcess(
        "child.exe",  // executable
        NULL, NULL, NULL,
        FALSE,
        0, NULL, NULL,
        &si, &pi
    );

    // Wait for child to finish
    WaitForSingleObject(pi.hProcess, INFINITE);

    // Cleanup
    UnmapViewOfFile(pBuf);
    CloseHandle(hMapFile);

    return 0;
}

