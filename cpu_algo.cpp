#include <bits/stdc++.h>
#include "include/cpu_algo.h"

#define MAX_SIZE_PROC 50

using namespace std;

/* 
Defining a process structure which contains

* Process Id
* Arrival Time
* Burst Time
* Turnaround Time
* Waiting Time

as its attributes
 */
struct Process {
    int pid;
    int at;
    int bt;
    int tat = 0;
    int wt = 0;
} arr[MAX_SIZE_PROC];

int n;

// Function to find turnaround time of each process for FCFS Algorithm
void findTAT() {
    for (int i=0; i<n; i++) {
        arr[i].tat = arr[i].bt + arr[i].wt;
    }
}

// Function to find waiting time of each process for FCFS Algorithm
void findWT_fcfs() {
    arr[0].wt = 0;
    for (int i=1; i<n; i++) {
        arr[i].wt = arr[i-1].wt + arr[i-1].bt;
    }
}

// Function to find waiting time of each process for SRTF Algorithm
void findWT_srtf() {
    
    // Initializing an array to hold remaining time values
    int *rt = new int(n);
    for (int i=0; i<n; i++) {
        rt[i] = arr[i].bt;
    }

    int completed = 0, t = 0, mintime = INT_MAX, shortest;
    bool flag = false;

    // Running while loop until all processes are completed
    while (completed != n) {

        // Finding process with shortest remaining time
        for (int i=0; i < n && arr[i].at <= t; i++) {
            if (rt[i] < mintime && rt[i] > 0) {
                mintime = rt[i];
                shortest = i;
                flag = true;
            } 
        }

        // Check if no process was found
        if (!flag) {
            t++;
            continue;
        }

        // Update remaining time of shortest process and update minimim time value
        rt[shortest]--;
        mintime = rt[shortest];
        
        // Check if shortest process is completed
        if (rt[shortest] == 0) {
            mintime = INT_MAX;
            completed++;
            flag = false;

            arr[shortest].wt = t + 1 - arr[shortest].bt - arr[shortest].at;
        }
        t++;
    }
}

// Function to find waiting time of each process for Round Robin Algorithm
void findWT_rr(int q) {
    
    // Initializing an array to hold remaining time values
    int *rt = new int(n);
    for (int i=0; i<n; i++) {
        rt[i] = arr[i].bt;
    }

    int completed = 0, t = 0;
    bool flag = false;

    // Running while loop until all processes are completed
    while (completed != n) {

        // Looping through all available processes
        for (int i=0; i < n && arr[i].at <= t; i++) {

            // Check if remaining time is greater than 1 quantum. If true then run the process for 1 quantum
            if (rt[i] > q) {
                flag = true;
                t += q;
                rt[i] -= q;
            } 

            // Check if remaining time is less than or equal to 1 quantum, but process is not yet finished. If true then run for remaining time 
            else if (rt[i] > 0) {
                flag = true;
                t += rt[i];
                completed++;
                rt[i] = 0;

                arr[i].wt = t - arr[i].bt - arr[i].at;
            }
        }

        if (flag) {
            flag = false;
        }
        else {
            t++;
        }
    }
}

bool cmp (Process p1, Process p2) {
    return (p1.at < p2.at);
}

// Function to input the processes from the user
void inputProcessesCPU() {
    cout << "Enter the number of processes: ";
    cin >> n;

    for (int i=0; i < n; i++) {
        cout << "\n\nFor Process " << i;
        cout << "\n--------------\n";
        cout << "Enter the Arrival Time: ";
        cin >> arr[i].at;
        cout << "Enter the Burst Time: ";
        cin >> arr[i].bt;

        arr[i].pid = i;
    }

    sort(arr, arr + n, cmp);
}

// Function to display the results to the user
void displayResultCPU() {
    float avgTAT = 0, avgWT = 0;

    cout << "\nPID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n\n";
    for (int i=0; i<n; i++) {
        cout << left << setw(8) << arr[i].pid;
        cout << left << setw(17) << arr[i].at;
        cout << left << setw(15) << arr[i].bt;
        cout << left << setw(17) << arr[i].wt;
        cout << left << setw(20) << arr[i].tat << endl;

        avgTAT += arr[i].tat;
        avgWT += arr[i].wt;
    }

    cout << "\nAverage Waiting Time: " << (avgWT / n) << endl;
    cout << "Average Turnaround Time: " << (avgTAT / n) << "\n\n";
}

void CPU_Scheduling() {
    int choice, quantum;
    inputProcessesCPU();

    cout << "\nCPU Scheduling Algorithm\n";
    cout << "1. First Come First Serve (FCFS)\n";
    cout << "2. Shortest Job First (SJF)\n";
    cout << "3. Longest Job First (LJF)\n";
    cout << "4. Shortest Remaining Time First (SRTF)\n";
    cout << "5. Longest Remaining Time First (LRTF)\n";
    cout << "6. Round Robin (RR)\n";
    cout << "\nEnter your choice: ";
    cin >> choice;

    switch(choice) {
        case 1: {
            findWT_fcfs();
            findTAT();
            cout << "\nUsing FCFS Scheduling Algorithm:\n";
            displayResultCPU();

            break;
        }
        case 2: {
            // TODO

            break;
        }
        case 3: {
            // TODO

            break;
        }

        case 4: {
            findWT_srtf();
            findTAT();
            cout << "Using the Shortest Remaining Time First Algorithm:\n";
            displayResultCPU();

            break;
        }
        case 5: {
            // TODO

            break;
        }
        case 6: {
            cout << "\nEnter the value of time quantum: ";
            cin >> quantum;
            findWT_rr(quantum);
            findTAT();
            cout << "Using the Round Robin Algorithm with time quantum = " << quantum << ":\n";
            displayResultCPU();

            break;
        }
        default: "\nInvalid choice entered...\n";
    }


}