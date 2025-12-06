#include <stdio.h>

int main() {
    int n, i, j;
    int bt[20], wt[20], tat[20], p[20], temp;
    float avg_wt = 0, avg_tat = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter burst time for each process:\n");
    for(i = 0; i < n; i++) {
        printf("P%d: ", i+1);
        scanf("%d", &bt[i]);
        p[i] = i + 1;   // process numbers
    }

    // Sort by burst time (simple bubble sort)
    for(i = 0; i < n - 1; i++) {
        for(j = 0; j < n - i - 1; j++) {
            if(bt[j] > bt[j+1]) {
                temp = bt[j];
                bt[j] = bt[j+1];
                bt[j+1] = temp;

                temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
        }
    }

    // Waiting time for first process is 0
    wt[0] = 0;

    // Calculate waiting times
    for(i = 1; i < n; i++) {
        wt[i] = wt[i-1] + bt[i-1];
    }

    // Calculate TAT
    for(i = 0; i < n; i++) {
        tat[i] = wt[i] + bt[i];
    }

    // Print results
    printf("\nProcess\tBurst Time\tWaiting Time\tTurn Around Time\n");
    for(i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\t\t%d\n", p[i], bt[i], wt[i], tat[i]);
        avg_wt += wt[i];
        avg_tat += tat[i];
    }

    avg_wt /= n;
    avg_tat /= n;

    printf("\nAverage Waiting Time = %.2f", avg_wt);
    printf("\nAverage Turn Around Time = %.2f\n", avg_tat);

    return 0;
}

