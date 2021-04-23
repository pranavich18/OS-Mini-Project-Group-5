// Compile the following program with -pthread flag > g++ -pthread 191CS141_ReaderWriter.cpp
#include <pthread.h>
#include <iostream>
#include <iomanip>
#include <queue>
#include <string>
#include "include/reader_writer.h"

// Defining the maximum size of the buffer
#define BufferSize 6

using namespace std;

// Initializing the write semaphore
int wrt=1;
pthread_mutex_t mutex;

// Initializing the number of initial readers to 0
int num_readers = 0;

// Initializing the read/write buffer
int buffer[BufferSize];
int in = -1;

// Creating the structure for a process, containing PID, Arrival Time, Burst Time and flag variable for producer/consumer check
struct Process {
    int pid;
    int at;
    int bt;
    bool is_wrt;
};

// Wait function that will wait for a signal to be positive
void wait(int *s) {
    while (*s <= 0);
    (*s)--;
}

// Post function that increases the value of a given signal
void post(int *s) {
    (*s)++;
}

// Function for writer to write data to the buffer
void *writer(void *process)
{   
    pthread_mutex_trylock(&mutex);
    wait(&wrt);
    int data = rand();
    buffer[++in] = data;

    // Printing statement to show what the current writer has written, but this line causes issues in code hence it is commented
    // cout <<  "Writer " << ((Process *)process)->pid << " wrote " << data << " into the buffer.\n";
    post(&wrt);
    pthread_mutex_unlock(&mutex);

}

// Function for reader to read data from the buffer
void *reader(void *process)
{   
    pthread_mutex_trylock(&mutex);
    num_readers++;

    // If this is the first reader, then it will block the writer
    if(num_readers == 1) {
        wait(&wrt);
    }
    pthread_mutex_unlock(&mutex);

    int data = buffer[max(in, 0)];

    // Printing statement to show what the current reader has read, but this line causes issues in code hence it is commented
    // cout << "Reader " << ((Process *)process)->pid << " read " << data << " from the buffer.\n";

    pthread_mutex_trylock(&mutex);
    num_readers--;

    // If this is the last reader, it will wake up the writer.
    if(num_readers == 0) {
        post(&wrt);
    }
    pthread_mutex_unlock(&mutex);
}

// Driver Function
int reader_writer()
{   
    int t=0, m=0, n=0;
    // STL Queue to implement FCFS for the processes
    queue<Process> processes;

    // String to print appropriate message when multiple users try to access buffer
    string msg;

    // PThread arrays to create threads
    pthread_t read[3],write[3];

    // Initialize the mutex
    pthread_mutex_init(&mutex, NULL);

    // Array of writers
    struct Process writers[3] = {
        {1, 0 ,2, true},
        {2, 1, 3, true},
        {3, 2, 2, true}
    };

    // Array of readers
    struct Process readers[3] = {
        {1, 0 ,2, false},
        {2, 1, 2, false},
        {3, 2, 3, false}
    };

    // Add elements to queue in FCFS method, giving higher priority to writers
    while (processes.size() != 6) {
        for (int i=0; i<3; i++) {
            if (writers[i].at == t) {
                processes.push(writers[i]);
            }
        }
        for (int i=0; i<3; i++) {
            if (readers[i].at == t) {
                processes.push(readers[i]);
            }
        }
        t++;
    }

    t = 0;

    // Simulation of FCFS process scheduling
    while (!(processes.empty())) {
        Process currProcess = processes.front();
        processes.pop();

        // If current process is a writer
        if (currProcess.is_wrt) {
            if (in >= BufferSize) {
                cout << "Buffer is full so writers can no longer write.\n\n";
                return 0;
            }
            pthread_create(&write[m++], NULL, writer, (void *)&currProcess);
            msg = "writer ";
        }
        // If current process is a reader
        else {
            pthread_create(&read[n++], NULL, reader, (void *)&currProcess);
            msg = "reader ";
            if (in < 0) {
                cout << "Buffer is empty so reader cannot read.\n\n";
            }
        }

        string msgnext = (processes.front().is_wrt) ? "writer " : "reader ";

        // If the next process is a writer, or if current process is writer and next process is reader
        if (!(processes.empty()) && (currProcess.bt + t > processes.front().at) && (processes.front().is_wrt || (processes.front().is_wrt != currProcess.is_wrt))) {
            cout << "At t=" << t << ", buffer is being used by " << msg << currProcess.pid;
            cout << ". Therefore, " << msgnext << processes.front().pid << " cannot access the buffer.\n\n";
            t += currProcess.bt;
        }
        // If the current process and next process are both readers
        else if (!(processes.empty()) && currProcess.is_wrt == false && processes.front().is_wrt == false) {
            if (t + currProcess.bt < processes.front().at + processes.front().bt) {
                t = processes.front().at + processes.front().bt;
            }
            else {
                t += currProcess.bt;
            }
            processes.pop();
        }
        

    }

    // Exiting statements for threads
    pthread_mutex_destroy(&mutex);

    return 0;
    
}