#include <bits/stdc++.h>
#include "include/dining_philosopher.h"

using namespace std;

struct user{
    int id; 
    int arvl;  // arrival time
    int arvl_i; // used during waiting
    int burst;  // burst time
    int burst_i; // remaining burst time
    int left_hand;  // left hand first
    int right_hand; // right hand first
    struct user *left;
    struct user *right;
    int comp;
};

void dining_philosopher(){

    int i = 0, time = 0;
    int users;
    cout << "\nEnter number of people: ";
    cin >> users;
    struct user phil[users];
    
    // User input of all processes
    for (i = 0; i < users; i++) {
        phil[i].id = i + 1;
        phil[i].left_hand = phil[i].right_hand = 0;
        cout << "\nEnter the arrival and burst time of philosopher " << phil[i].id << " : ";
        cin >> phil[i].arvl;
        cin >> phil[i].burst;
        phil[i].arvl_i = phil[i].arvl;
        phil[i].burst_i = phil[i].burst;
        phil[i].comp = -1;
        
        if (i == users - 1){
            phil[i].right = &phil[0];
            phil[0].left = &phil[i];
        }
        else{
            phil[i].right = &phil[i + 1];
            phil[i + 1].left = &phil[i];
        }
    }
    int left = users;
    int p = 1;

    // runs until all the processes are completed
    while (left) {
        for (i = 0; i < users; i++){
            
            if (phil[i].comp >= 0)
                continue;
            if (phil[i].comp == -1 && phil[i].arvl_i <= time){
                
                if (phil[i].right -> left_hand == 0 && phil[i].right_hand == 0)
                {
                    phil[i].right_hand = 1;
                    cout << "\nPhilosopher " << phil[i].id << " has taken the right stick and checking for left stick if available \n";
                }
            }
        }
        int dead = users;
        for (i = 0; i < users; i++){
            if (phil[i].right_hand)
                dead--;
        }
        
        if (dead == 0){
            cout << "\nDeadend......solving! by giving " << users << "th stick to the philosopher 1\n";

            phil[0].left_hand = 1;
            phil[0].left -> right_hand = 0;
            phil[0].left -> comp = -1;
            phil[0].comp = 0;
        }

        for (i = 0; i < users; i++){
            if (phil[i].comp >= 0 || phil[i].right_hand == 0)
                continue; 

            if (phil[i].right_hand){
                if (phil[i].left -> right_hand == 0 && phil[i].left_hand == 0){
                    phil[i].left_hand = 1;
                    phil[i].comp = 0;
                    cout << "\nPhilosopher " << phil[i].id << " has picked up the left stick and right stick and ready to dine\n";
                }
                else{
                    if (p)
                        cout << "\nPhilosopher " << phil[i].id << " is waiting for the left stick till the left philosopher to complete his/her turn\n";
                }
            }
        }
        
        p = 0;
        for (i = 0; i < users; i++){
            if (phil[i].comp < 0)
                continue;
            if (phil[i].comp == 0){

                phil[i].burst_i--;
                if (phil[i].burst_i == 0){
                    cout << "\nPhilosopher " << phil[i].id << " has finished his job and sticks are placed back\n";
                    p = 1;
                    left--;
                    phil[i].right_hand = 0;
                    phil[i].left_hand = 0;
                    phil[i].comp = time + 1;
                }
            }
            else if (phil[i].comp == 0){
                phil[i].arvl_i++;
            }
        }
        time++;
    }
    
    int dead = 1;
    for (i = 0; i < users; i++){
        if (phil[i].comp > 0)
            dead = 0;
        cout << "\nPhilosopher id: " << phil[i].id << " -> " << " arrival time " << phil[i].arvl << " burst time " << phil[i].burst << " completed at " << phil[i].comp;
    }
    if (dead){
        cout << "\n-1 in comp indicates dead end\n";
    }
}
