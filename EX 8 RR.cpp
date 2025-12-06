#include <stdio.h>
int main() {
    int n, i, tq, time = 0, remaining;
    int bt[20], rt[20], wt[20], tat[20];
    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter burst time for each process:\n");
    for(i = 0; i < n; i++) 
	{
        printf("P%d: ", i+1);
        scanf("%d", &bt[i]);
        rt[i] = bt[i];   
		 }
    printf("Enter time quantum: ");
    scanf("%d", &tq);
    remaining = n;
    while(remaining > 0)
	 {
        for(i = 0; i < n; i++)
		 {
            if(rt[i] > 0) {
                if(rt[i] > tq) {
                    time += tq;
                    rt[i] -= tq;
                } else {
                    time += rt[i];
                    tat[i] = time;
                    wt[i] = tat[i] - bt[i];
                    rt[i] = 0;
                    remaining--;
                }
            }
        }
    }
    printf("\nProcess\tBT\tWT\tTAT\n");
    float avg_wt = 0, avg_tat = 0;
    for(i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\n", i+1, bt[i], wt[i], tat[i]);
        avg_wt += wt[i];
        avg_tat += tat[i];
    }
    printf("\nAverage Waiting Time = %.2f", avg_wt / n);
    printf("\nAverage Turn Around Time = %.2f\n", avg_tat / n);
    return 0;
}
