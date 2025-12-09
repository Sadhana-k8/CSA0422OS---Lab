#include <stdio.h>

int main() {
    int n, m; 
    int alloc[10][10], max[10][10], avail[10];
    int need[10][10], finish[10] = {0}, safeseq[10];
    int i, j, k, count = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resource types: ");
    scanf("%d", &m);

    printf("\nEnter Allocation Matrix:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++)
            scanf("%d", &alloc[i][j]);
    }

    printf("\nEnter Maximum Requirement Matrix:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++)
            scanf("%d", &max[i][j]);
    }

    printf("\nEnter Available Resources:\n");
    for (i = 0; i < m; i++)
        scanf("%d", &avail[i]);

    // Calculate Need Matrix
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++)
            need[i][j] = max[i][j] - alloc[i][j];
    }

    printf("\nNeed Matrix:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++)
            printf("%d ", need[i][j]);
        printf("\n");
    }

    // Banker's Algorithm
    while (count < n) {
        int found = 0;
        for (i = 0; i < n; i++) {
            if (!finish[i]) {
                int flag = 0;
                for (j = 0; j < m; j++) {
                    if (need[i][j] > avail[j]) {
                        flag = 1;
                        break;
                    }
                }
                if (!flag) {
                    for (k = 0; k < m; k++)
                        avail[k] += alloc[i][k];
                    finish[i] = 1;
                    safeseq[count++] = i;
                    found = 1;
                }
            }
        }
        if (!found) {
            printf("\nSystem is in DEADLOCK. No safe sequence.\n");
            return 0;
        }
    }

    printf("\nSAFE SEQUENCE: ");
    for (i = 0; i < n; i++)
        printf("P%d ", safeseq[i]);

    printf("\nSystem is in SAFE STATE.\n");
    return 0;
}

