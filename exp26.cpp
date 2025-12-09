#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int choice;
    char filename[50], newfilename[50], data[100];
    FILE *fp;

    while (1) {
        printf("\n--- FILE MANAGEMENT OPERATIONS ---\n");
        printf("1. Create File\n");
        printf("2. Write to File\n");
        printf("3. Read File\n");
        printf("4. Delete File\n");
        printf("5. Rename File\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Consume newline

        switch (choice) {
            case 1:
                printf("Enter filename to create: ");
                scanf("%s", filename);
                fp = fopen(filename, "w");
                if (fp == NULL) {
                    printf("Error creating file.\n");
                } else {
                    printf("File '%s' created successfully.\n", filename);
                    fclose(fp);
                }
                break;

            case 2:
                printf("Enter filename to write: ");
                scanf("%s", filename);
                fp = fopen(filename, "a");
                if (fp == NULL) {
                    printf("Error opening file.\n");
                } else {
                    printf("Enter data to write: ");
                    getchar(); // consume newline
                    fgets(data, sizeof(data), stdin);
                    fprintf(fp, "%s", data);
                    fclose(fp);
                    printf("Data written successfully.\n");
                }
                break;

            case 3:
                printf("Enter filename to read: ");
                scanf("%s", filename);
                fp = fopen(filename, "r");
                if (fp == NULL) {
                    printf("Error opening file.\n");
                } else {
                    printf("File contents:\n");
                    while (fgets(data, sizeof(data), fp) != NULL) {
                        printf("%s", data);
                    }
                    fclose(fp);
                }
                break;

            case 4:
                printf("Enter filename to delete: ");
                scanf("%s", filename);
                if (remove(filename) == 0)
                    printf("File '%s' deleted successfully.\n", filename);
                else
                    printf("Unable to delete file.\n");
                break;

            case 5:
                printf("Enter current filename: ");
                scanf("%s", filename);
                printf("Enter new filename: ");
                scanf("%s", newfilename);
                if (rename(filename, newfilename) == 0)
                    printf("File renamed successfully to '%s'.\n", newfilename);
                else
                    printf("Error renaming file.\n");
                break;

            case 6:
                printf("Exiting program...\n");
                exit(0);

            default:
                printf("Invalid choice! Try again.\n");
        }
    }

    return 0;
}

