#include <stdio.h>
#include <string.h>

struct
{
    char dname[20];        // Directory name
    char fname[20][20];    // File names
    int fcount;            // Number of files
} dir;

int main()
{
    int choice;
    char searchfile[20];

    dir.fcount = 0;

    printf("Enter directory name: ");
    scanf("%s", dir.dname);

    while (1)
    {
        printf("\n--- SINGLE LEVEL DIRECTORY ---\n");
        printf("1. Create File\n");
        printf("2. Search File\n");
        printf("3. Display Files\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
        {
            printf("Enter file name: ");
            scanf("%s", dir.fname[dir.fcount]);
            dir.fcount++;
            printf("File created successfully!\n");
            break;
        }

        case 2:
        {
            printf("Enter file name to search: ");
            scanf("%s", searchfile);

            int found = 0;   // DECLARATION SAFE NOW

            for (int i = 0; i < dir.fcount; i++)
            {
                if (strcmp(searchfile, dir.fname[i]) == 0)
                {
                    printf("File '%s' found in directory '%s'.\n",
                           searchfile, dir.dname);
                    found = 1;
                    break;
                }
            }
            if (!found)
                printf("File not found!\n");

            break;
        }

        case 3:
        {
            printf("\nDirectory Name: %s\n", dir.dname);
            printf("Files:\n");

            for (int i = 0; i < dir.fcount; i++)
            {
                printf("%s\n", dir.fname[i]);
            }
            break;
        }

        case 4:
            printf("Exiting program...\n");
            return 0;

        default:
            printf("Invalid choice!\n");
        }
    }
}

