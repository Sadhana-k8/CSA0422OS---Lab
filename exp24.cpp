#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main() {
    int fd;
    char filename[50];
    char data[100];
    char readbuffer[100];

    printf("Enter the filename to create: ");
    scanf("%s", filename);

    // Create a file
    fd = open(filename, O_CREAT | O_WRONLY, 0644);
    if (fd == -1) {
        printf("Error in creating file.\n");
        return 1;
    }
    printf("File '%s' created successfully.\n", filename);

    // Write to the file
    printf("Enter data to write in the file: ");
    getchar(); // consume newline
    fgets(data, sizeof(data), stdin);
    write(fd, data, strlen(data));
    close(fd);
    printf("Data written to file successfully.\n");

    // Read the file
    fd = open(filename, O_RDONLY);
    if (fd == -1) {
        printf("Error in opening file for reading.\n");
        return 1;
    }
    int n = read(fd, readbuffer, sizeof(readbuffer) - 1);
    readbuffer[n] = '\0'; // Null-terminate
    close(fd);

    printf("\nData read from file '%s':\n", filename);
    printf("%s\n", readbuffer);

    return 0;
}

