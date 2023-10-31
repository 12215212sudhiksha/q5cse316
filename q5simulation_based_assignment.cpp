#include <stdio.h>
#include <stdlib.h>

struct Process {
    char process_name[50];
    int arrival_time;
    int burst_time;
    int completion_time;
    int remaining;
};

// Function for sorting processes by arrival time
int ArrivalTimeComparator(const void* a, const void* b) {
    return ((struct Process*)a)->arrival_time - ((struct Process*)b)->arrival_time;
}

// Function to perform Round Robin scheduling for a given queue
void roundRobinScheduling(struct Process* processQueue, int num_processes, int quantum_time, int* total_query_time) {
    int time = 0; // Track the current time

    while (1) {
        int allProcessesCompleted = 1;

        for (int i = 0; i < num_processes; i++) {
            if (processQueue[i].remaining > 0) {
                allProcessesCompleted = 0;

                if (processQueue[i].remaining <= quantum_time) {
                    time += processQueue[i].remaining;
                    *total_query_time += time - processQueue[i].arrival_time;
                    processQueue[i].completion_time = time;
                    processQueue[i].remaining = 0;
                } else {
                    time += quantum_time;
                    processQueue[i].remaining -= quantum_time;
                }
            }
        }

        if (allProcessesCompleted) {
            break;
        }
    }
}

int main() {
    int select_queue, num_processes;
    int total_query_time = 0; // Variable to store total query time

    printf("Please choose a queue to post your query:\n");
    printf("1. FACULTY queue\n");
    printf("2. STUDENT queue\n");
    printf("> ");
    scanf("%d", &select_queue);

    struct Process* processQueue;

    printf("Enter the number of processes: ");
    scanf("%d", &num_processes);
    processQueue = (struct Process*)malloc(num_processes * sizeof(struct Process));

    for (int i = 0; i < num_processes; i++) {
        printf("Enter the details of Process[%d]\n", i + 1);
        printf("Process Name: ");
        scanf("%s", processQueue[i].process_name);
        printf("Arrival Time: ");
        scanf("%d", &processQueue[i].arrival_time);
        printf("Burst Time: ");
        scanf("%d", &processQueue[i].burst_time);
        processQueue[i].remaining = processQueue[i].burst_time; // Initialize remaining time
    }

    // Sort processes by arrival time using the ArrivalTimeComparator function
    qsort(processQueue, num_processes, sizeof(struct Process), ArrivalTimeComparator);

    int quantum_time;
    printf("Enter the quantum time: ");
    scanf("%d", &quantum_time);

    // Perform Round Robin scheduling for the chosen queue
    roundRobinScheduling(processQueue, num_processes, quantum_time, &total_query_time);

    // Print the results
    printf("\n\t\t\t_________________________________\n");
    printf("\t\t\t __ ROUND ROBIN ALGORITHM OUTPUT __ \n");
    printf("\t\t\t_____________________________________\n");
    printf("| Process Name       | Arrival Time | Burst Time | Completion Time | Waiting Time | Turnaround Time |\n");

    for (int i = 0; i < num_processes; i++) {
        int waiting_time = processQueue[i].completion_time - processQueue[i].burst_time - processQueue[i].arrival_time;
        if (waiting_time < 0) {
            waiting_time = 0; // Ensure waiting time is non-negative
        }

        int turnaround_time = processQueue[i].completion_time - processQueue[i].arrival_time;
        printf("| %-19s | %-12d | %-10d | %-15d | %-12d | %-15d |\n",
               processQueue[i].process_name, processQueue[i].arrival_time, processQueue[i].burst_time,
               processQueue[i].completion_time, waiting_time, turnaround_time);
    }

    // Calculate and print the average query time
    double average_query_time = (double)total_query_time / num_processes;
    printf("\nAverage Query Time: %lf\n", average_query_time);

    // Print the total query time
    printf("Total Query Time: %d\n", total_query_time);

    free(processQueue); // Free the dynamically allocated memory

    return 0;
}

