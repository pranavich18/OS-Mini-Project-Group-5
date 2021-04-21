#include <bits/stdc++.h>
#include "include/paging_algo.h"

using namespace std;

//Function to simulate FIFO paging
void paging_fifo(){
    int n = 0, i = 0, choice, frames, page_no, pages, page_faults = 0;
    int vsize, psize, pagesize, offset;
    int fno = 0;
    unordered_set <int> page;
    unordered_map <int, int> page_frame;
    queue <int> index;

    // Check for positive integer input
    do{
    cout << "\nEnter size of virtual memory(in KB): ";
    cin >> vsize;
    }while(vsize <= 0);

    // Check for positive integer input
    do{
        cout << "Enter size of physical memory(in KB): ";
        cin >> psize;
    }while(psize <= 0);

    // Check for positive integer input
    do{
        cout << "Enter size of page(in KB): ";
        cin >> pagesize;
    }while(pagesize <= 0);

    cout << "\nNumber of pages in virtual memory: " << (vsize / pagesize) << endl;
    cout << "Number of frames in physical memory: " << (psize / pagesize) << endl;
    pages = (vsize / pagesize);
    frames = (psize / pagesize);

    while(1){
        cout << "\nMenu:\n";
        cout << "1. Enter virtual address in the <Page Number | Word Offset> format\n";
        cout << "2. Stop " << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        
        //Switch based on user inputted choice
        switch(choice){

            case 1: {
            do{
            cout << "Enter Page Number and Word Offset (offset in byte): ";
            cin >> page_no;
            cin >> offset;
            } while(offset <= 0 || page_no < 0);
            
            if(page_no >= pages){
                cout << "ERROR! Entered page number is not present in Virtual Memory" << endl;
                continue;
            }
            if(offset > pagesize * pow(2, 10)){
                cout << "ERROR! Entered offset exceeds page size" << endl;
                continue;
            }
            
            // If all the frames are not filled yet
            if (page.size() < frames){
                
                // If the page does not exist in a frame, increase page fault and add the page to a frame
                if (page.find(page_no) == page.end()){
                    page.insert(page_no);
                    index.push(page_no);
                    page_frame.insert({page_no, fno});
                    page_faults++;
                    cout << "Page number " << page_no << " is not present in physical memory so it has been accomodated in frame " << fno << endl;
                    fno++;          
                }

                // If the page already exists in a frame, print appropriate message
                else {
                    cout << "The physical address for the above virtual address is " << page_frame[page_no] << " | " << offset << endl;
                }   
            }

            // If all the frames are filled
            else{
                
                // If the page does not exist in a frame, remove page according to first in first out 
                if (page.find(page_no) == page.end()){
                    int val = index.front();
                    index.pop();
                    page.erase(val);
                    page.insert(page_no);
                    page_frame.erase(val);
                    page_frame.insert({page_no, fno});
                    page_faults++;
                    cout << "Page number " << page_no << " is not present in physical memory so it has been accomodated after removing page number " << val << " according to FIFO" << endl;
                }
                
                // If the page already exists in a frame, print appropriate message
                else{
                cout << "The physical address for the above virtual address is " << page_frame[page_no] << " | " << offset << endl;
                }
            }

            //Increment n for the size of input
            n += 1;
            break;
            }

            case 2: {
                cout << "No. of page faults: " << page_faults << endl;
                cout << "Page fault ratio: " << (float)page_faults / (float)n << endl;
                
                int temp;
                // Print the frame location of each page
                cout << "\nPage \tFrame \n";
                for(int i = 0; i < pages; i++){
                    temp = 0;
                    for(auto itr = page_frame.find(i); itr != page_frame.end(); itr++){
                        cout << itr -> first << "\t" << itr -> second << endl;
                        temp = 1;
                        break;
                    }
                    if(temp == 0)
                    cout << i << "\t" << -1 << endl;
                }

                // Print the page present in each frame
                cout << "\nFrame \tPage \n";
                for(auto it = page_frame.begin(); it != page_frame.end(); it++){
                    cout << it -> second << "\t" << it -> first << endl;
                }
                exit(0);
            }
            default: cout << "Invalid input entered..Enter again\n";
        }
    }
}

//Function to simulate LRU paging
void paging_lru(){
    int n = 0, i = 0, choice, frames, page_no, pages, page_faults = 0;
    int vsize, psize, pagesize, offset;
    int fno = 0;
    unordered_set <int> page;
    unordered_map <int, int> page_frame;
    unordered_map <int, int> index;
    
    // Check for positive integer input
    do{
    cout << "\nEnter size of virtual memory(in KB): ";
    cin >> vsize;
    }while(vsize <= 0);

    // Check for positive integer input
    do{
        cout << "Enter size of physical memory(in KB): ";
        cin >> psize;
    }while(psize <= 0);

    // Check for positive integer input
    do{
        cout << "Enter size of page(in KB): ";
        cin >> pagesize;
    }while(pagesize <= 0);

    cout << "\nNumber of pages in virtual memory: " << (vsize / pagesize) << endl;
    cout << "Number of frames in physical memory: " << (psize / pagesize) << endl;
    pages = (vsize / pagesize);
    frames = (psize / pagesize);

    while(1){
        cout << "\nMenu:\n";
        cout << "1. Enter virtual address in the <Page Number | Word Offset> format\n";
        cout << "2. Stop " << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        
        //Switch based on user inputted choice
        switch(choice){

            case 1: {
            do{
            cout << "Enter Page Number and Word Offset (offset in byte): ";
            cin >> page_no;
            cin >> offset;
            } while(offset <= 0 || page_no < 0);
            
            if(page_no >= pages){
                cout << "ERROR! Entered page number is not present in Virtual Memory" << endl;
                continue;
            }
            if(offset > pagesize * pow(2, 10)){
                cout << "ERROR! Entered offset exceeds page size" << endl;
                continue;
            }

            // If all the frames are not filled yet
            if (page.size() < frames){
                
                // If the page does not exist in a frame, increase page fault and add the page to a frame
                if (page.find(page_no) == page.end()){
                    page.insert(page_no);
                    page_frame.insert({page_no, fno});
                    page_faults++;
                    cout << "Page number " << page_no << " is not present in physical memory so it has been accomodated in frame " << fno << endl;
                    fno++;          
                }

                // If the page already exists in a frame, print appropriate message
                else {
                    cout << "The physical address for the above virtual address is " << page_frame[page_no] << " | " << offset << endl;
                }
                index[page_no] = i;
            }

            // If all the frames are filled
            else{
                
                // If the page does not exist in a frame, remove least recently used page
                if (page.find(page_no) == page.end()){
                    int lru = INT8_MAX, val;
                    for(auto it = page.begin(); it != page.end(); it++){
                        if(index[*it] < lru){
                                lru = index[*it];
                                val = *it;
                        }
                    }
                    page.erase(val);
                    page.insert(page_no);
                    page_frame.erase(val);
                    page_frame.insert({page_no, fno});
                    page_faults++;
                    cout << "Page number " << page_no << " is not present in physical memory so it has been accomodated after removing page number " << val << " according to LRU" << endl;
                }

                // If the page already exists in a frame, print appropriate message
                else{
                cout << "The physical address for the above virtual address is " << page_frame[page_no] << " | " << offset << endl;
                }
                index[page_no] = i;
            }
            
            //Increment n for the size of input
            n += 1; 
            i += 1;
             break;
            }

            case 2 : {
                cout << "No. of page faults: " << page_faults << endl;
                cout << "Page fault ratio: " << (float)page_faults / (float)n << endl;
                
                int temp;
                // Print the frame location of each page
                cout << "\nPage \tFrame \n";
                for(int i = 0; i < pages; i++){
                    temp = 0;
                    for(auto itr = page_frame.find(i); itr != page_frame.end(); itr++){
                        cout << itr -> first << "\t" << itr -> second << endl;
                        temp = 1;
                        break;
                    }
                    if(temp == 0)
                    cout << i << "\t" << -1 << endl;
                }

                // Print the page present in each frame
                cout << "\nFrame \tPage \n";
                for(auto it = page_frame.begin(); it != page_frame.end(); it++){
                    cout << it -> second << "\t" << it -> first << endl;
                }
                exit(0);
            }
            default: cout << "Invalid input entered..Enter again\n";
        }
    }
}

//MRU paging
// Initialize a global array of frames, pages along with some necessary global variables
int frames[MAX_SIZE], pagetable[MAX_SIZE], disk[MAX_SIZE];
int size = 0, t = 0, capacity, page_fault = 0, n_pages, n_tracks, thead;

// Initialize a global hash map to store the time of entry of each page
unordered_map<int, int> pages;

// Function to simulate MRU Paging
void MRUPaging(int page, int offset)
{
    // If all the frames are not filled yet
    if (size < capacity) {
        for (int i = 0; i < capacity; i++) {
            
            // If the page already exists in a frame, print appropriate message and return
            if (frames[i] == page) {
                pages[page] = t++;
                cout << "\nThe physical address of Page " << page << " is: " << i << " | " << offset << endl;
                return;
            }
        }
        
        // If the page does not exist in a frame, increase page fault and add the page to a frame
        cout << "\nPage " << page << " is not present in Physical memory.\n";
        cout << "Page " << page << " accomodated at Frame " << size << endl;

        pagetable[page] = size;
        frames[size++] = page;
        page_fault++;
        pages[page] = t++;
        return;
    }

    // If all the frames are filled
    for (int i = 0; i < capacity; i++) {
        
        // If the page already exists in a frame, print appropriate message and return 
        if (frames[i] == page) {
            pages[page] = t++;
            cout << "\nThe physical address of Page " << page << " is: " << i << " | " << offset << endl;
            return;
        }
    }
    
    int mru_t = -1, val;
    // If the page does not exist in a frame, find the Most Recently Used page to remove
    for (int j=0; j < capacity; j++) {
        if (pages[frames[j]] > mru_t) {
            mru_t = pages[frames[j]];
            val = j;
        }
    }
    
    // Print the appropriate message, increase page fault and add the page to a frame
    cout << "\nPage " << page << " is not present in Physical memory.\n";
    cout << "Page " << page << " accomodated at Frame " << val << " after removing Page " << frames[val] <<  " by MRU method\n";

    pagetable[frames[val]] = -1;
    frames[val] = page;
    pagetable[page] = val;
    page_fault++;
    pages[page] = t++;
}

// Function to display the pages and frames allocated before exiting the program
void display(float n_in) {
    
    // Print the total page fauts, page fault ratio
    cout << "\nTotal Page Faults: " << page_fault;
    cout << "\nPage Fault Ratio: " << page_fault / n_in;

    // Print the frame location of each page
    cout << "\n\nPage \tFrame \n";
    for (int i = 0; i < n_pages; i++) {
        cout << i << "\t" << pagetable[i] << endl;
    }

    // Print the page present in each frame
    cout << "\n\nFrame \tPage \n";
    for (int i = 0; i < capacity; i++) {
        cout << i << "\t" << frames[i] << endl;
    }
}


//Function to simulate MRU paging
void paging_mru(){
    fill_n(frames, MAX_SIZE, -1);
    fill_n(pagetable, MAX_SIZE, -1);
    int choice, pno, res, psize, vsize, pagesize, offset;
    float n_in = 0;

    // Check for positive integer input
    do {
        cout << "\nEnter the size of virtual memory: ";
        cin >> vsize;
    } while (vsize <= 0);
    
    // Check for positive integer input
    do {
        cout << "Enter the size of physical memory: ";
        cin >> psize;
    } while (psize <= 0);

    // Check for positive integer input
    do {
        cout << "Enter the size of each page: ";
        cin >> pagesize;
    } while (pagesize <= 0);

    // Calculate the number of pages and frames
    capacity = psize / pagesize;
    n_pages = vsize / pagesize;

    // Print the total number of pages and frames
    cout << "\nNumber of Pages in virtual memory: " << n_pages;
    cout << "\nNumber of Frames in physical memory: " << capacity;

    // Program Menu will always show unless the user decides to quit
    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Enter virtual address in the <Page Number | Word Offset> format\n";
        cout << "2. Stop " << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        // Switch based on user inputted choice
        switch(choice) {
            // MRU Paging case
            case 1: {
                do {
                    cout << "\nEnter the page number and word offset: ";
                    cin >> pno >> offset;
                } while (pno < 0 || pno < 0);

                if(pno >= n_pages){
                cout << "ERROR! Entered page number is not present in Virtual Memory" << endl;
                continue;
                }
                if(offset > pagesize * pow(2, 10)){
                cout << "ERROR! Entered offset exceeds page size" << endl;
                continue;
                }

                MRUPaging(pno, offset);
                
                // Increment the value of n_in for number of inputs
                n_in++;
                break;
            }
            // Quit case
            case 2: {
                display(n_in);
                exit(0);
            }
            // Default case for invalid input
            default: cout << "\nInvalid choice entered..Enter again\n";
        }
    }

}

void paging(){
    int choice;
    
    //List out the supported paging algorithms
    cout << "\nPaging Algorithms:\n";
    cout << "1. First In First Out (FIFO)\n";
    cout << "2. Least Recently Used (LRU)\n";
    cout << "3. Most Recently Used (MRU)\n";
    cout << "Enter your choice:";
    cin >> choice;

    //switch case based on user input
    switch(choice){
        //FIFO case
        case 1: paging_fifo();
                break;

        //LRU case        
        case 2: paging_lru();
                break;

        //MRU case        
        case 3: paging_mru();
                break;

        //default case to handle invalid user inputs        
        default: cout << "Invalid choice entered\n";
    } 
}
