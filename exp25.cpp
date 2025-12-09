#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>

int main() {
    int fd, flags;
    char filename[50];
    char buffer[100];
    struct stat filestat;
    DIR *d;
    struct dirent *dir;

    printf("Enter filename to create/open: ");
    scanf("%s", filename);

    // Open file (create if not exist)
    fd = open(filename, O_CREAT | O_RDWR, 0644);
    if (fd == -1) {
        perror("open");
        return 1;
    }
    printf("File '%s' opened/created successfully.\n", filename);

    // Write to file
    write(fd, "Hello UNIX I/O system calls!\n", 29);

    // Use fcntl to get and set file descriptor flags
    flags = fcntl(fd, F_GETFL);
    printf("Current file flags: %d\n", flags);
    fcntl(fd, F_SETFL, flags | O_APPEND);
    printf("O_APPEND flag set.\n");

    // Seek to beginning
    lseek(fd, 0, SEEK_SET);

    // Read from file
    int n = read(fd, buffer, sizeof(buffer) - 1);
    buffer[n] = '\0';
    printf("File content:\n%s\n", buffer);

    // Get file status using stat
    if (stat(filename, &filestat) == 0) {
        printf("\nFile Information:\n");
        printf("Size: %ld bytes\n", filestat.st_size);
        printf("Permissions: %o\n", filestat.st_mode & 0777);
    }

    close(fd);

    // Open current directory and list files
    printf("\nDirectory contents:\n");
    d = opendir(".");
    if (d) {
        while ((dir = readdir(d)) != NULL) {
            printf("%s\n", dir->d_name);
        }
        closedir(d);
    }

    return 0;
}

