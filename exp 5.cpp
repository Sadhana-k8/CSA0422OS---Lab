#include <stdio.h>

struct Process {
    int pid;        // Process ID
    int bt;         // Burst Time
    int priority;   // Priority (higher number = higher priority)
    int wt;         // Waiting Time
    int tat;        // Turnaround Time
};

int main() {
    int n, i, j;
    struct Process p[10];
    struct Process temp;
    int total_wt = 0, total_tat = 0;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    // Input burst time and priority
    for (i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter burst time for Process %d: ", i + 1);
        scanf("%d", &p[i].bt);
        printf("Enter priority for Process %d: ", i + 1);
        scanf("%d", &p[i].priority);
    }

    // Sort processes by priority (higher priority first)
    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if (p[i].priority < p[j].priority) {
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }

    // Calculate waiting time
    p[0].wt = 0; // First process waiting time = 0
    for (i = 1; i < n; i++) {
        p[i].wt = p[i - 1].wt + p[i - 1].bt;
    }

    // Calculate turnaround time
    for (i = 0; i < n; i++) {
        p[i].tat = p[i].wt + p[i].bt;
    }

    // Display results
    printf("\nProcess\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\n");
    for (i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\t\t%d\t\t%d\n", p[i].pid, p[i].bt, p[i].priority, p[i].wt, p[i].tat);
        total_wt += p[i].wt;
        total_tat += p[i].tat;
    }

    printf("\nAverage Waiting Time: %.2f", (float)total_wt / n);
    printf("\nAverage Turnaround Time: %.2f\n", (float)total_tat / n);

    return 0;
}

