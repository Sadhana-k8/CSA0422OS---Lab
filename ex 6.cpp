#include <stdio.h>

struct Process {
    int pid;
    int at;     // Arrival Time
    int bt;     // Burst Time
    int rt;     // Remaining Time
    int priority;
    int ct;     // Completion Time
    int tat;    // Turnaround Time
    int wt;     // Waiting Time
};

int main() {
    int n, time = 0, completed = 0, i, highest;
    struct Process p[20];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("\nEnter arrival time of P%d: ", i + 1);
        scanf("%d", &p[i].at);
        printf("Enter burst time of P%d: ", i + 1);
        scanf("%d", &p[i].bt);
        printf("Enter priority of P%d: ", i + 1);
        scanf("%d", &p[i].priority);
        p[i].rt = p[i].bt;
    }

    printf("\n--- Preemptive Priority Scheduling ---\n");

    while (completed != n) {
        highest = -1;

        // Choose the highest priority process that has arrived
        for (i = 0; i < n; i++) {
            if (p[i].at <= time && p[i].rt > 0) {
                if (highest == -1 || p[i].priority > p[highest].priority) {
                    highest = i;
                }
            }
        }

        if (highest != -1) {
            p[highest].rt--;  // Execute process for 1 unit

            // If finished
            if (p[highest].rt == 0) {
                completed++;
                p[highest].ct = time + 1;
                p[highest].tat = p[highest].ct - p[highest].at;
                p[highest].wt = p[highest].tat - p[highest].bt;
            }
        }

        time++; // Move clock
    }

    printf("\nPID\tAT\tBT\tPRIO\tCT\tTAT\tWT\n");
    for (i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].at, p[i].bt, p[i].priority,
               p[i].ct, p[i].tat, p[i].wt);
    }

    return 0;
}

