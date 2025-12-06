#include <stdio.h>
#include <fcntl.h>
#include <io.h>
#include <stdlib.h>

int main() {
    char srcFile[100], destFile[100];
    int src, dest;
    char buffer[1024];
    int bytesRead;

    printf("Enter source filename: ");
    scanf("%s", srcFile);

    printf("Enter destination filename: ");
    scanf("%s", destFile);

    // Open source file
    src = _open(srcFile, _O_RDONLY);
    if (src < 0) {
        perror("Error opening source file");
        return 1;
    }

    // Open destination file
    dest = _open(destFile, _O_WRONLY | _O_CREAT | _O_TRUNC, 0644);
    if (dest < 0) {
        perror("Error opening destination file");
        _close(src);
        return 1;
    }

    // Copy contents
    while ((bytesRead = _read(src, buffer, sizeof(buffer))) > 0) {
        _write(dest, buffer, bytesRead);
    }

    _close(src);
    _close(dest);

    printf("File copied successfully!\n");
    return 0;
}

