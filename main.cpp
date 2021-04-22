#include <bits/stdc++.h>

// Import all the individual programs
#include "include/Bankers.h"
#include "include/cpu_algo.h"
#include "include/reader_writer.h"
#include "include/paging_algo.h"
#include "include/mvt.h"
#include "include/Disk_Scheduling.h"
#include "include/producer_consumer.h"
#include "include/mft.h"
#include "include/title.h"

using namespace std;

int main() {
	int c;

	// Function to print the welcome prompt
	printTitle();

	// Main Menu displays until user chooses to quit
	while(true) {
		cout << "\n              MAIN MENU\n";
		cout << "-------------------------------------\n";
		cout << "1. Execute CPU Scheduling Algorithms\n";
		cout << "2. Execute Producer Consumer Problem\n";
		cout << "3. Execute Reader Writer Problem\n";
		cout << "4. Execute Dining Philosopher Problem\n";
		cout << "5. Execute MFT Memory Management\n";
		cout << "6. Execute MVT Memory Management\n";
		cout << "7. Execute Sleeping Barber's Problem\n";
		cout << "8. Execute Paging Algorithms\n";
		cout << "9. Execute Disk Scheduling Algorithms\n";
		cout << "\nPress 0 to quit\n";
		cout << "Enter your choice: ";
		cin >> c;
		cout << "-------------------------------------\n";

		// Switch case based on user input
		switch(c) {
			// CPU Scheduling Case
			case 1: {
				CPU_Scheduling();
				break;
			}
			// Producer Consumer Case
			case 2: {
				producer_consumer();
				break;
			}
			// Reader Writer Case
			case 3: {
				reader_writer();
				break;
			}
			// Dining Philosopher Case
			case 4: {
				// TODO
				break;
			}
			// MFT Case
			case 5: {
				mft();
				break;
			}
			// MVT Case
			case 6: {
				mvt();
				break;
			}
			// Sleeping Barber Case
			case 7: {
				// TODO
				break;
			}
			// Paging Case
			case 8: {
				paging();
				break;
			}
			// Disk Scheduling Case
			case 9: {
				Disk_Scheduling();
				break;
			}
			// Exit Case
			case 0: {
				cout << "\nThank you for using the simulator!\n\n";
				exit(0);
			}
			// Default Case to handle invalid inputs
			default: cout << "\nInvalid choice entered...\n";
		}
	}
	return 0;
}
