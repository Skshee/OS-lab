#include <stdio.h>
#include <stdlib.h>

#define MAX_PROCESSES 100

typedef struct {
    int id;
    int burst_time;
    int arrival_time;
    int priority;
    int remaining_time; // For preemptive SJF and RR
} Process;

void preemptive_sjf(Process processes[], int n);
void round_robin(Process processes[], int n, int quantum);
void non_preemptive_priority(Process processes[], int n);
void calculate_waiting_time(Process processes[], int n, int waiting_time[]);
void calculate_turnaround_time(Process processes[], int n, int turnaround_time[]);

int main() {
    int choice, n, quantum;
    Process processes[MAX_PROCESSES];

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        printf("Enter burst time for process %d: ", processes[i].id);
        scanf("%d", &processes[i].burst_time);
        printf("Enter arrival time for process %d: ", processes[i].id);
        scanf("%d", &processes[i].arrival_time);
        printf("Enter priority for process %d (lower number indicates higher priority): ", processes[i].id);
        scanf("%d", &processes[i].priority);
        processes[i].remaining_time = processes[i].burst_time; // Initialize remaining time
    }

    do {
        printf("\nMenu:\n");
        printf("1. Preemptive Shortest Job First (SJF)\n");
        printf("2. Round Robin (RR)\n");
        printf("3. Non-Preemptive Priority Scheduling\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                preemptive_sjf(processes, n);
                break;
            case 2:
                printf("Enter time quantum for Round Robin: ");
                scanf("%d", &quantum);
                round_robin(processes, n, quantum);
                break;
            case 3:
                non_preemptive_priority(processes, n);
                break;
            case 4:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 4);

    return 0;
}

void preemptive_sjf(Process processes[], int n) {
    int time = 0, completed = 0;
    int waiting_time[MAX_PROCESSES] = {0};
    int turnaround_time[MAX_PROCESSES] = {0};

    while (completed < n) {
        int idx = -1;
        int min_burst = 9999;

        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= time && processes[i].remaining_time > 0) {
                if (processes[i].remaining_time < min_burst) {
                    min_burst = processes[i].remaining_time;
                    idx = i;
                }
            }
        }

        if (idx != -1) {
            processes[idx].remaining_time--;
            time++;

            if (processes[idx].remaining_time == 0) {
                completed++;
                turnaround_time[idx] = time - processes[idx].arrival_time;
                waiting_time[idx] = turnaround_time[idx] - processes[idx].burst_time;
            }
        } else {
            time++;
        }
    }

    printf("\nPreemptive SJF Scheduling:\n");
    printf("Process\tBurst Time\tArrival Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].id, processes[i].burst_time, processes[i].arrival_time, waiting_time[i], turnaround_time[i]);
    }
}

void round_robin(Process processes[], int n, int quantum) {
    int time = 0, completed = 0;
    int waiting_time[MAX_PROCESSES] = {0};
    int turnaround_time[MAX_PROCESSES] = {0};
    int remaining_time[MAX_PROCESSES];

    for (int i = 0; i < n; i++) {
        remaining_time[i] = processes[i].burst_time;
    }

    while (completed < n) {
        int all_done = 1; // Flag to check if all processes are done in this round

        for (int i = 0; i < n; i++) {
            if (remaining_time[i] > 0 && processes[i].arrival_time <= time) {
                all_done = 0; // At least one process is still pending

                if (remaining_time[i] > quantum) {
                    time += quantum;
                    remaining_time[i] -= quantum;
                } else {
                    time += remaining_time[i];
                    waiting_time[i] = time - processes[i].burst_time - processes[i].arrival_time;
                    turnaround_time[i] = time - processes[i].arrival_time;
                    remaining_time[i] = 0;
                    completed++;
                }
            }
        }


    printf("\nRound Robin Scheduling:\n");
    printf("Process\tBurst Time\tArrival Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].id, processes[i].burst_time, processes[i].arrival_time, waiting_time[i], turnaround_time[i]);
    }
}

void non_preemptive_priority(Process processes[], int n) {
    int time = 0, completed = 0;
    int waiting_time[MAX_PROCESSES] = {0};
    int turnaround_time[MAX_PROCESSES];
    int is_completed[MAX_PROCESSES] = {0};

    while (completed < n) {
        int idx = -1;
        int highest_priority = 9999;

        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= time && !is_completed[i]) {
                if (processes[i].priority < highest_priority) {
                    highest_priority = processes[i].priority;
                    idx = i;
                }
            }
        }

        if (idx != -1) {
            time += processes[idx].burst_time;
            turnaround_time[idx] = time - processes[idx].arrival_time;
            waiting_time[idx] = turnaround_time[idx] - processes[idx].burst_time;
            is_completed[idx] = 1;
            completed++;
        } else {
            time++;
        }
    }

    printf("\nNon-Preemptive Priority Scheduling:\n");
    printf("Process\tBurst Time\tArrival Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].id, processes[i].burst_time, processes[i].arrival_time, waiting_time[i], turnaround_time[i]);
    }
}
