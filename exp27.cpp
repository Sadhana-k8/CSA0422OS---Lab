#include <stdio.h>
#include <dirent.h>

int main() {
    DIR *d;
    struct dirent *dir;
    char path[100];

    printf("Enter directory path to list files (or '.' for current directory): ");
    scanf("%s", path);

    d = opendir(path);
    if (d == NULL) {
        printf("Cannot open directory %s\n", path);
        return 1;
    }

    printf("\nContents of directory '%s':\n", path);
    while ((dir = readdir(d)) != NULL) {
        printf("%s\n", dir->d_name);
    }

    closedir(d);
    return 0;
}

