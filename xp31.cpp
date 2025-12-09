#include <stdio.h>

int main() {
    int n, frames, i, j, k, flag, fifoIndex = 0, pageFaults = 0;

    printf("Enter number of pages: ");
    scanf("%d", &n);

    int pages[n];
    printf("Enter page reference sequence:\n");
    for (i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    printf("Enter number of frames: ");
    scanf("%d", &frames);

    int frameArr[frames];
    for (i = 0; i < frames; i++)
        frameArr[i] = -1; // Initialize frames as empty

    printf("\nPage Replacement Process (FIFO):\n");
    printf("Ref\tFrames\n");

    for (i = 0; i < n; i++) {
        flag = 0;

        // Check if page is already in frame
        for (j = 0; j < frames; j++) {
            if (frameArr[j] == pages[i]) {
                flag = 1;
                break;
            }
        }

        // Page fault occurs
        if (!flag) {
            frameArr[fifoIndex] = pages[i];  // Replace page using FIFO index
            fifoIndex = (fifoIndex + 1) % frames;
            pageFaults++;
        }

        // Display current frame status
        printf("%d\t", pages[i]);
        for (j = 0; j < frames; j++) {
            if (frameArr[j] != -1)
                printf("%d ", frameArr[j]);
            else
                printf("- ");
        }
        printf("\n");
    }

    printf("\nTotal Page Faults: %d\n", pageFaults);

    return 0;
}

