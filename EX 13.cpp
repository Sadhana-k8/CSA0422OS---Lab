#include <stdio.h>

void firstFit(int blockSize[], int m, int processSize[], int n) {
    int allocation[n];
    for (int i = 0; i < n; i++)
        allocation[i] = -1;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (blockSize[j] >= processSize[i]) {
                allocation[i] = j;
                blockSize[j] -= processSize[i];
                break;
            }
        }
    }

    printf("\nFirst Fit Allocation:\n");
    for (int i = 0; i < n; i++)
        (allocation[i] != -1) ? 
            printf("Process %d -> Block %d\n", i, allocation[i]) :
            printf("Process %d -> Not Allocated\n", i);
}

void bestFit(int blockSize[], int m, int processSize[], int n) {
    int allocation[n];
    for (int i = 0; i < n; i++)
        allocation[i] = -1;

    for (int i = 0; i < n; i++) {
        int bestIndex = -1;
        for (int j = 0; j < m; j++) {
            if (blockSize[j] >= processSize[i]) {
                if (bestIndex == -1 || blockSize[j] < blockSize[bestIndex])
                    bestIndex = j;
            }
        }
        if (bestIndex != -1) {
            allocation[i] = bestIndex;
            blockSize[bestIndex] -= processSize[i];
        }
    }

    printf("\nBest Fit Allocation:\n");
    for (int i = 0; i < n; i++)
        (allocation[i] != -1) ?
            printf("Process %d -> Block %d\n", i, allocation[i]) :
            printf("Process %d -> Not Allocated\n", i);
}

void worstFit(int blockSize[], int m, int processSize[], int n) {
    int allocation[n];
    for (int i = 0; i < n; i++)
        allocation[i] = -1;

    for (int i = 0; i < n; i++) {
        int worstIndex = -1;
        for (int j = 0; j < m; j++) {
            if (blockSize[j] >= processSize[i]) {
                if (worstIndex == -1 || blockSize[j] > blockSize[worstIndex])
                    worstIndex = j;
            }
        }
        if (worstIndex != -1) {
            allocation[i] = worstIndex;
            blockSize[worstIndex] -= processSize[i];
        }
    }

    printf("\nWorst Fit Allocation:\n");
    for (int i = 0; i < n; i++)
        (allocation[i] != -1) ?
            printf("Process %d -> Block %d\n", i, allocation[i]) :
            printf("Process %d -> Not Allocated\n", i);
}

int main() {
    int m, n;

    printf("Enter number of memory blocks: ");
    scanf("%d", &m);
    int blockSize[m];

    printf("Enter size of each block:\n");
    for (int i = 0; i < m; i++)
        scanf("%d", &blockSize[i]);

    printf("\nEnter number of processes: ");
    scanf("%d", &n);
    int processSize[n];

    printf("Enter size of each process:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &processSize[i]);

    // Preserve original block sizes
    int b1[50], b2[50], b3[50];
    for (int i = 0; i < m; i++)
        b1[i] = b2[i] = b3[i] = blockSize[i];

    firstFit(b1, m, processSize, n);
    bestFit(b2, m, processSize, n);
    worstFit(b3, m, processSize, n);

    return 0;
}

