#include <stdio.h>
#include <string.h>

struct
{
    char dname[20];           // Directory name
    char fname[20][20];       // Files inside directory
    int fcount;               // Number of files
} subdir[20];                 // Multiple sub-directories

int main()
{
    int i, j, ch, count = 0;
    char dsearch[20], fsearch[20];

    while (1)
    {
        printf("\n--- TWO LEVEL DIRECTORY ---\n");
        printf("1. Create Directory\n");
        printf("2. Create File\n");
        printf("3. Search File\n");
        printf("4. Display Directory\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &ch);

        switch (ch)
        {
        case 1: // Create directory
            printf("Enter directory name: ");
            scanf("%s", subdir[count].dname);
            subdir[count].fcount = 0;
            count++;
            printf("Directory created!\n");
            break;

        case 2: // Create file in a directory
            printf("Enter directory name: ");
            scanf("%s", dsearch);
            for (i = 0; i < count; i++)
            {
                if (strcmp(dsearch, subdir[i].dname) == 0)
                {
                    printf("Enter file name: ");
                    scanf("%s", subdir[i].fname[subdir[i].fcount]);
                    subdir[i].fcount++;
                    printf("File created!\n");
                    break;
                }
            }
            if (i == count)
                printf("Directory not found!\n");
            break;

        case 3: // Search file
            printf("Enter directory name: ");
            scanf("%s", dsearch);

            for (i = 0; i < count; i++)
            {
                if (strcmp(dsearch, subdir[i].dname) == 0)
                {
                    printf("Enter file name to search: ");
                    scanf("%s", fsearch);

                    for (j = 0; j < subdir[i].fcount; j++)
                    {
                        if (strcmp(fsearch, subdir[i].fname[j]) == 0)
                        {
                            printf("File '%s' found in directory '%s'.\n",
                                   fsearch, dsearch);
                            break;
                        }
                    }

                    if (j == subdir[i].fcount)
                        printf("File not found!\n");
                    break;
                }
            }

            if (i == count)
                printf("Directory not found!\n");
            break;

        case 4: // Display all directories and files
            printf("\n--- DIRECTORY STRUCTURE ---\n");
            for (i = 0; i < count; i++)
            {
                printf("\nDirectory: %s\n", subdir[i].dname);
                printf("Files:\n");

                for (j = 0; j < subdir[i].fcount; j++)
                    printf("  %s\n", subdir[i].fname[j]);
            }
            break;

        case 5:
            printf("Exiting...");
            return 0;

        default:
            printf("Invalid choice!\n");
        }
    }
}

