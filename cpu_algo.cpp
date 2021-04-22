#include <bits/stdc++.h>
#include "include/cpu_algo.h"

// Define the maximum size of processes
#define MAX_SIZE_PROC 50

using namespace std;

/* 
Defining a process structure which contains

* Process Id
* Arrival Time
* Burst Time
* Turnaround Time
* Waiting Time

as its attributes.
Also create a global array of processes
 */
struct Process {
    int pid;
    int at;
    int bt;
    int tat = 0;
    int wt = -1;
} arr[MAX_SIZE_PROC];

// Global variable to store the number of processes
int n;

// Function to find turnaround time of each process
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

// Function to find waiting time of each process for SJF Algorithm
void findWT_sjf() {
    int completed = 0, t = 0, mintime = INT_MAX, shortest;
    bool flag = false;

    // Outer loop is run till all processes are complete
    while (completed < n) {

        // Finding process with shortest burst time
        for (int i=0; i < n && arr[i].at <= t; i++) {
            if (arr[i].bt < mintime && arr[i].wt < 0) {
                mintime = arr[i].bt;
                shortest = i;
                flag = true;
            } 
        }

        // Check if no process was found
        if (!flag) {
            t++;
            continue;
        }       
        // If shortest process is found, complete the process
        else {
            mintime = INT_MAX;
            flag = false;
            completed++;

            arr[shortest].wt = t - arr[shortest].at;
            t += arr[shortest].bt;
        }
    }
}

// Function to find waiting time of each process for LJF Algorithm
void findWT_ljf() {
    int completed = 0, t = 0, maxtime = INT_MIN, longest;
    bool flag = false;

    // Outer loop is run till all processes are complete
    while (completed < n) {

        // Finding process with longest burst time
        for (int i=0; i < n && arr[i].at <= t; i++) {
            if (arr[i].bt > maxtime && arr[i].wt < 0) {
                maxtime = arr[i].bt;
                longest = i;
                flag = true;
            } 
        }

        // Check if no process was found
        if (!flag) {
            t++;
            continue;
        }       
        // If longest process is found, complete the process
        else {
            maxtime = INT_MIN;
            flag = false;
            completed++;

            arr[longest].wt = t - arr[longest].at;
            t += arr[longest].bt;
        }
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

        // Update remaining time of shortest process and update minimum time value
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

// Function to find waiting time of each process for LRTF Algorithm
void findWT_lrtf() {
    
    // Initializing an array to hold remaining time values
    int *rt = new int(n);
    for (int i=0; i<n; i++) {
        rt[i] = arr[i].bt;
    }

    int completed = 0, t = 0, maxtime = INT_MIN, longest;
    bool flag = false;

    // Running while loop until all processes are completed
    while (completed != n) {

        // Finding process with longest remaining time
        for (int i=0; i < n && arr[i].at <= t; i++) {
            if (rt[i] > maxtime && rt[i] > 0) {
                maxtime = rt[i];
                longest = i;
                flag = true;
            } 
        }

        // Check if no process was found
        if (!flag) {
            t++;
            continue;
        }

        // Update remaining time of longest process and update maximum time value
        rt[longest]--;
        maxtime = rt[longest];
        
        // Check if longest process is completed
        if (rt[longest] == 0) {
            maxtime = INT_MIN;
            completed++;
            flag = false;

            arr[longest].wt = t + 1 - arr[longest].bt - arr[longest].at;
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

// Function to find waiting time of each process for HRRN Algorithm
void findWT_hrrn() {
    int completed = 0, t = 0, maxtime = INT_MIN, longest;
    float resptime, wt;
    bool flag = false;

    // Outer loop is run till all processes are complete
    while (completed < n) {

        // Finding process with highest response ratio time
        for (int i=0; i < n && arr[i].at <= t; i++) {
            if (arr[i].wt < 0) {
                wt = t - arr[i].at;
                resptime = (wt + arr[i].bt) / arr[i].bt;
                if (resptime > maxtime) {
                    maxtime = resptime;
                    longest = i;
                    flag = true;
                }
            } 
        }

        // Check if no process was found
        if (!flag) {
            t++;
            continue;
        }       
        // If process is found, complete the process
        else {
            maxtime = INT_MIN;
            flag = false;
            completed++;

            arr[longest].wt = t - arr[longest].at;
            t += arr[longest].bt;
        }
    }
}

// Helper function to sort processes based on their arrival times
bool cmp (Process p1, Process p2) {
    return (p1.at < p2.at);
}

// Function to input the processes from the user
void inputProcessesCPU() {
    // Check for positive integer input
    do {
        cout << "\nEnter the number of processes: ";
        cin >> n;
    } while (n <= 0);

    // Input the arrival and burst times for each process
    for (int i=0; i < n; i++) {
        cout << "\n\nFor Process " << i;
        cout << "\n--------------\n";
        cout << "Enter the Arrival Time: ";
        cin >> arr[i].at;
        cout << "Enter the Burst Time: ";
        cin >> arr[i].bt;

        arr[i].pid = i;
        arr[i].tat = 0;
        arr[i].wt = -1;
    }

    // Sort the processes based on their arrival times
    sort(arr, arr + n, cmp);
}

// Function to display the results to the user
void displayResultCPU() {
    float avgTAT = 0, avgWT = 0;

    cout << "\nPID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n\n";

    // Print the results for each process in the array
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

// Top Level function used in main.cpp, this is the only function accessible through cpu_algo.h
void CPU_Scheduling() {
    int choice, quantum, ret = 0;

    // Input the processes from the user
    inputProcessesCPU();

    // Program menu will display until user chooses to return to main menu
    while (true) {
        // List out the supported CPU Scheduling Algorithms
        cout << "\n\nChoose CPU Scheduling Algorithm\n";
        cout << "-------------------------------\n";
        cout << "1. First Come First Serve (FCFS)\n";
        cout << "2. Shortest Job First (SJF)\n";
        cout << "3. Longest Job First (LJF)\n";
        cout << "4. Shortest Remaining Time First (SRTF)\n";
        cout << "5. Longest Remaining Time First (LRTF)\n";
        cout << "6. Round Robin (RR)\n";
        cout << "7. Highest Response Ratio Next (HRRN)\n";
        cout << "\nEnter your choice: ";
        cin >> choice;

        // Switch case based on User Input
        switch(choice) {
            // FCFS Case
            case 1: {
                findWT_fcfs();
                findTAT();
                cout << "\nUsing FCFS Scheduling Algorithm:\n";
                displayResultCPU();

                break;
            }
            // SJF Case
            case 2: {
                findWT_sjf();
                findTAT();
                cout << "\nUsing SJF Scheduling Algorithm:\n";
                displayResultCPU();

                break;
            }
            // LJF Case
            case 3: {
                findWT_ljf();
                findTAT();
                cout << "\nUsing LJF Scheduling Algorithm:\n";
                displayResultCPU();

                break;
            }
            // SRTF Case
            case 4: {
                findWT_srtf();
                findTAT();
                cout << "\nUsing the SRTF Algorithm:\n";
                displayResultCPU();

                break;
            }
            // LRTF Case
            case 5: {
                findWT_lrtf();
                findTAT();
                cout << "\nUsing the LRTF Algorithm:\n";
                displayResultCPU();

                break;
            }
            // RR Case
            case 6: {
                cout << "\nEnter the value of time quantum: ";
                cin >> quantum;
                findWT_rr(quantum);
                findTAT();
                cout << "\nUsing the Round Robin Algorithm with time quantum = " << quantum << ":\n";
                displayResultCPU();

                break;
            }
            // HRRN Case
            case 7: {
                findWT_hrrn();
                findTAT();
                cout << "\nUsing the HRRN Algorithm:\n";
                displayResultCPU();

                break;
            }
            // Default case to handle invalid user inputs
            default: "\nInvalid choice entered...\n";
        }

        // Next option menu
        cout << "\nChoose next option:\n";
        cout << "-------------------\n";
        cout << "1. Input Processes again\n";
        cout << "2. Use a different CPU Scheduling Algorithm\n";
        cout << "3. Return to Main Menu\n";
        cout << "\nEnter your choice: ";
        cin >> choice;

        // Switch case based user inputted choice
        switch(choice) {
            // Input new processes
            case 1: {
                inputProcessesCPU();

                break;
            }
            // Use different scheduling algorithm with same processes
            case 2: {
                // Reset the waiting times and turnaround times for each process
                for (int i=0; i < n; i++) {
                    arr[i].wt = -1;
                    arr[i].tat = 0;
                }

                break;
            }
            // Exit to main menu
            case 3: {
                ret = 1;

                break;
            }
            // Default case to handle invalid user inputs
            default: "\nInvalid choice entered...\n";
        }

        // Check if ret variable is set to 1, and return to main menu if true
        if (ret == 1) {
            break;
        }
    }
}