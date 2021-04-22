#include<bits/stdc++.h>
#include "include/mft.h"

using namespace std;

struct Partition {
    int size;
    int pid = -1;
    int psize = 0;
} partitions[50];

int n_part, n_proc, int_frag = 0, size;
int total_size,n_parts,unused;
vector<pair<int,int>> parts;
vector<int> v;

void print_best(){
    int extfrag = 0;
    cout<<"Unused space : "<<unused<<"\nFinal state of all partitions\nPNo\tPID\tSpace Used\tSpace Free\n";
    for(int i=0;i<parts.size();i++){
        cout<<i<<'\t'<<v[i]<<'\t'<<parts[i].first-parts[i].second<<"\t\t"<<parts[i].second<<'\n';
        extfrag += parts[i].second;
    }
    cout<<"External fragmentation : "<<extfrag<<"\n";
}



void remove_best(){
    int pid;
    cout<<"Enter ID of the process to be deleted : ";
    cin>>pid;
    for(int i=0;i<v.size();i++){
        if(v[i] == pid){
            cout<<"Process "<<pid<<" has been removed from partition "<<i<<"\n";
            v[i] = -1;
            parts[i].second = parts[i].first;
            return;
        }
    }
    cout<<"Process "<<pid<<" is not in any partition\n";
}

//function to insert a new process
void insert_best(){
    int pid,size,in=-1,mn=INT_MAX,extfrag=0;
    bool intfrag = false,too_big=true;
    cout<<"Enter process ID : ";
    cin>>pid;
    cout<<"Enter process size in KB : ";
    cin>>size;
    for(int i=0;i<parts.size();i++){
        if(parts[i].first>=size) too_big=false;
        if(parts[i].first == parts[i].second){
            if(parts[i].first>=size and parts[i].first<mn){
                mn = parts[i].first;
                in = i;
            }
        }
        else if (parts[i].second >= size) intfrag = true;
        extfrag+=parts[i].second;
    }
    if(in != -1){
        cout<<"Process "<<pid<<" is accomodated in Partition "<<in<<"\n";
        parts[in].second -= size;
        v[in] = pid;
        return;
    }
    cout<<"Process "<<pid<<" could not be accomodated because";
    if(too_big) cout<<" it is greater than the size of the largest partition\n";
    else if(intfrag) cout<<" of internal fragmentation\n";
    else if(extfrag >= size) cout<<" of external fragmentation\n";
    else cout<<" there are no free partitions of sufficient size\n";
}



void insert_worst(int pid, int size, int worst_idx) {
    partitions[worst_idx].pid = pid;
    partitions[worst_idx].psize = size;
    // If the partition size is greater than the size of the process, increase internal fragmentation
    if (partitions[worst_idx].size > size) {
        int_frag += partitions[worst_idx].size - size;
    }
    // Update the value of number of processes
    n_proc++;

    cout << "Process " << pid <<  " allocated to Partition " << worst_idx << " successfully!\n";
}

void inputPartition_worst() {
    int i, off = 0;
    // Run the loop for num_partitions times
    for (i = 0; i < n_part; i++) {
        cout << "\nFor Partition " << i - off << "\n----------------\n";
        // Check for positive integer input
        do {
            cout << "Enter the size: ";
            cin >> partitions[i-off].size;
        } while (partitions[i-off].size <= 0);

        // If the partition size exceeds the remaining size of the buffer, print appropriate error message and continue
        if (size - partitions[i-off].size < 0) {
            cout << "Partition " << i << " cannot be given any space as only " << size << "KB space is remaining.\n";
            off++;
            continue;
        }
        // If a partition was successfully assigned, reduce the amount of available space in the buffer
        size -= partitions[i-off].size;
    }

    // Update the total number of partitions to the number of partitions that were successfully added
    n_part = i-off;
    cout << endl << n_part << " Partitions entered successfully!\n\n";
}

void worstFit(int pid, int size) {
    int curr_size = 0, worst_idx = -1;
    // Loop through the partitions and find the worst partition that can hold the process
    for (int i=0; i < n_part; i++) {
        if (partitions[i].pid == -1 && partitions[i].size >= size && partitions[i].size > curr_size) {
            worst_idx = i;
            curr_size = partitions[i].size;
        }
    }

    // If no partition was found, print the appropriate error message
    if (worst_idx == -1) {
        cout << "Process " << pid << " cannot be accomodated in memory.\n";
        return;
    }
    // If found, insert the process in the buffer
    insert_worst(pid, size, worst_idx);
}

void deleteProc_worst(int pid) {
    // Loop over all the partitions to find the required one to delete
    for (int i=0; i < n_part; i++) {
        if (partitions[i].pid == pid) {
            // Set the process number to -1 and update the remaining size and processes allocated
            partitions[i].pid = -1;
            size += partitions[i].psize;
            partitions[i].psize = 0;
            n_proc--;

            cout << "Process " << pid << " deleted from Partition " << i << " successfully!\n";
            return;
        }
    }
    cout << "Process not found!\n";
}

void mft_worst_fit(){
    int choice, pid, psize;
    // Check for positive integer input
    do {
        cout << "\nEnter the total size: ";
        cin >> size;
    } while (size <= 0);

    // Check for positive integer input
    do {
        cout << "\nEnter the number of partitions: ";
        cin >> n_part;
    } while (n_part <= 0);

    // Evaluate the partition inputs
    inputPartition_worst();

    // Program Menu will display until the user decides to quit
    while (true){ 
        cout << "\nProgram Menu\n";
        cout << "1. Insert process to buffer\n";
        cout << "2. Delete process from buffer\n";
        cout << "3. Quit\n";
        cout << "\nEnter your choice: ";
        cin >> choice;

        // Switch case on user input
        switch(choice) {
            // Insert Process
            case 1: {
                cout << "\nEnter the Process ID: ";
                cin >> pid;
                cout << "Enter the Process size: ";
                cin >> size;
                if (n_proc > n_part) {
                    cout << "Process " << pid << " cannot be given partition since only " << n_part << " partitions are available.\n";
                    break;
                }

                worstFit(pid, size);
                break;
            }
            // Delete Process
            case 2: {
                cout << "\nEnter the Process ID to delete: ";
                cin >> pid;

                deleteProc_worst(pid);
                break;
            }
            // Quit
            case 3: {
                // Print the total space remaining in the buffer and the total internal fragmentation
                cout << "\nSpace with no partition (External Fragmentation): " << size << "KB\n";
                cout << "Total Internal Fragmentation: " << int_frag << "KB\n\n";

                for (int i=0; i < n_part; i++) {
                    cout << "Partition " << i;
                    if (partitions[i].pid == -1) {
                        cout << " is empty!\n";
                    }
                    else {
                        cout << " is assigned to Process " << partitions[i].pid << endl;
                    }
                }
                cout << "\n\nThank you for using my program!\n\n";
                exit(0);
            }
        }
    }
}


void mft_first_fit(){
    int tot_size, n;
    int cnt_prt = 0; // variable to hold the number of partitions alloted
    cout << "Enter the total size: \n";
    cin >> tot_size;
    cout << "Enter the total number of partitions: \n";
    cin >> n;

    int space = tot_size; // variable for storing remaining space

    //array for storing the partition sizes
    int part[n + 1];
    for (int i = 1; i <= n; i++)
    {
        cout << "Enter the size of the partition " << i << ": ";
        cin >> part[i];

        //if the partition size is less than remaining space
        //allot the partition with that partition size
        if (part[i] <= space)
        {
            space -= part[i];
            cnt_prt++;
        }

        //otherwise partition cannot be alloted due to less remaining space
        else
        {
            cout << "Partition " << i << " cannot be alloted space because only " << space << "(units) space is remaining \n";
            part[i] = 0;
        }
    }
    int temp[n + 1];
    for (int i = 1; i <= n; i++)
    {
        temp[i] = part[i];
    }
    int ch = 1;
    int cnt_pro = 0;
    int input = 1;
    int allot_pro[100] = {0};
    int tot_frag = 0;
    int store[n + 1];
    int size[100];
    int empty_space = tot_size;
    while (ch != 3)
    {
        cout << "1.Insert \n";
        cout << "2.Delete \n";
        cout << "3.Stop \n";

        cout << "Enter the choice \n";
        cin >> ch;
        if (ch == 3)
            break;

        if (ch == 1)
        {

            cout << "Enter the size of process " << input << "\n";
            cin >> size[input];

            bool flag = false;

            //if the no of alloted processes exceeds the number of partitions
            //then processes cant be allocated
            if (cnt_pro >= cnt_prt)
            {
                cout << "process " << input << " cannot be given partition because only " << cnt_prt << " partitons are available " << endl;
                flag = true;
            }
            for (int j = 1; j <= n; j++)
            {
                //if the partition size is 0
                //process cant be alloted to that partition
                //so continue
                if (temp[j] == 0)
                    continue;

                //otherwise allot the required size for the process to the partition
                //and add remaining space to the internal fragmentation
                //part[j] = 0, indicating that partition is alloted
                if (size[input] <= temp[j])
                {
                    allot_pro[input] = j;
                    cout << "Process " << input << " is allocated to the partition " << j << "\n";
                    store[j] = input;
                    tot_frag += (temp[j] - size[input]);
                    empty_space -= size[input];
                    temp[j] = 0;
                    cnt_pro++;
                    flag = true;
                    break;
                }
            }
            if (!flag)
            {
                if (empty_space >= size[input])

                {
                    int cnt = false;
                    for (int i = 1; i <= n; i++)
                    {
                        if (size[input] <= part[i])
                        {
                            cout << "Process " << input << " cannot be accomodated due to external fragmentation \n";
                            cnt = true;
                            break;
                        }
                    }

                    if(!cnt)
                    {
                         cout << "Process " << input << " can't be given partition because it exceeds the size of all partitions \n";
                    }
                }

                    else 
                    cout << "Process " << input << " can't be given partition because it exceeds the size of all partitions \n";
                }
                input++;
            }

            else if (ch == 2)
            {
                int x;
                cout << "Enter the process id to be deleted  \n";
                cin >> x;
                bool found = false;
                //traversing the store array to find the partition
                // in which process x is stored
                for (int i = 1; i <= n; i++)
                {
                    if (store[i] == x)
                    {
                        temp[i] = part[i];
                        cnt_pro--;
                        allot_pro[x] = 0;
                        tot_frag -= (part[i] - size[x]);
                        empty_space += part[i];
                        found = true;
                        break;
                    }
                }
                if (!found)
                {
                    cout << "Process " << input << " is not present \n";
                }
            }
        }
        //printing the result
        for (int j = 1; j <= input; j++)
        {
            //if the process is allocated to some partition
            if (allot_pro[j] != 0)
                cout << "Process " << j << " is at partition " << allot_pro[j] << endl;
        }
        //printing the result
        cout << "\n";
        cout << "Space with no partition: " << space << "\n";
        cout << "Total internal fragmentation: " << tot_frag << "\n";
}


void mft_best_fit(){
cout<<"Enter total size of memory: ";
    cin>>total_size;
    cout<<"Enter number of partitions: ";
    cin>>n_parts;
    unused = total_size;
    for(int i=0;i<n_parts;i++){
        int temp_size;
        cout<<"Enter size of partition "<<i<<" :";
        cin>>temp_size;
        if(unused < temp_size){
            cout<<"Partition "<<i<<"cannot be given space because only "<<unused<<" KB of space is remaining\n";
            continue;
        }
        parts.push_back({temp_size,temp_size});
        unused -= temp_size;
    }
    v.resize(parts.size());

     int choice;
     while(true){
        cout<<"\n1.Insert\t2.Delete\t3.Exit\n";
        cin>>choice;
        switch(choice)
        {
            case 1:insert_best();
            break;
            case 2:remove_best();
            break;
            case 3: print_best();
            exit(1);
        }

    }
}



void mft(){
    cout<<"Enter the choice for Variable Partitioning Algorithms\n 1 for First Fit\n 2 for Best Fit\n 3 for Worst Fit\n 4 for Exit\n";
    int ch=0;
    while(ch!=4){
        cout<<"Enter you choice:\n";
        cin>>ch;
        if(ch==1){
            mft_first_fit();
        }
        else if(ch==2){
            mft_best_fit();
        }
        else if(ch==3){
            mft_worst_fit();
        }
        else if(ch==4)
            break;
        else
            cout<<"Wrong Choice!!\n";
    }
    return;
}