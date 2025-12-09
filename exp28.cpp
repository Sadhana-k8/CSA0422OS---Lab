#include <stdio.h>
#include <string.h>

int main() {
    FILE *fp;
    char filename[50];
    char line[256];
    char pattern[50];
    int found = 0;

    printf("Enter filename: ");
    scanf("%s", filename);

    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error: Cannot open file '%s'\n", filename);
        return 1;
    }

    printf("Enter pattern to search: ");
    scanf("%s", pattern);

    printf("\nLines containing '%s' in file '%s':\n", pattern, filename);

    while (fgets(line, sizeof(line), fp)) {
        if (strstr(line, pattern) != NULL) {
            printf("%s", line);
            found = 1;
        }
    }

    if (!found) {
        printf("No matching lines found.\n");
    }

    fclose(fp);
    return 0;
}

