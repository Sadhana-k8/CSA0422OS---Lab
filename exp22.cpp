#include <stdio.h>

int main() {
    int i, j, n, m;
    int blockSize[10], processSize[10], allocation[10];

    printf("Enter number of memory blocks: ");
    scanf("%d", &n);

    printf("Enter size of each block:\n");
    for (i = 0; i < n; i++)
        scanf("%d", &blockSize[i]);

    printf("Enter number of processes: ");
    scanf("%d", &m);

    printf("Enter size of each process:\n");
    for (i = 0; i < m; i++)
        scanf("%d", &processSize[i]);

    for (i = 0; i < m; i++)
        allocation[i] = -1; // Initialize allocation to -1 (not allocated)

    // Best Fit Allocation
    for (i = 0; i < m; i++) {
        int bestIdx = -1;
        for (j = 0; j < n; j++) {
            if (blockSize[j] >= processSize[i]) {
                if (bestIdx == -1 || blockSize[j] < blockSize[bestIdx])
                    bestIdx = j;
            }
        }
        if (bestIdx != -1) {
            allocation[i] = bestIdx;
            blockSize[bestIdx] -= processSize[i];
        }
    }

    // Display Results
    printf("\nProcess No.\tProcess Size\tBlock No.\n");
    for (i = 0; i < m; i++) {
        printf("%d\t\t%d\t\t", i + 1, processSize[i]);
        if (allocation[i] != -1)
            printf("%d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }

    return 0;
}

