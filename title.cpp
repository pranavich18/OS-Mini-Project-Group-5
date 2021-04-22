#include <bits/stdc++.h>
#include "include/title.h"

using namespace std;

void printTitle() {
    string members[10] = {
		"Nishant N Nayak - 191CS141",
        "Prachi Priyam Singh - 191CS142",
        "Prajwal J M - 191CS143",
        "Prakhar Singh - 191CS144",
		"Pranav Joshi - 191CS145",
		"Ragul N S - 191CS146",
        "Rakshit P - 191CS147",
		"Rakshith H R - 191CS148",
		"Reshma Tresa Antony - 191CS149",
		"Ritik Kumar - 191CS150"
	};

    cout << endl << string(87, '=') << "\n\n";
	
	cout << " .d88888b.   .d8888b.       8888888b.                   d8b                   888    \n";
	cout << "d88P\" \"Y88b d88P  Y88b      888   Y88b                  Y8P                   888    \n";
	cout << "888     888 Y88b.           888    888                                        888    \n";
	cout << "888     888  \"Y888b.        888   d88P 888d888 .d88b.  8888  .d88b.   .d8888b 888888 \n";
	cout << "888     888     \"Y88b.      8888888P\"  888P\"  d88\"\"88b \"888 d8P  Y8b d88P\"    888    \n";
	cout << "888     888       \"888      888        888    888  888  888 88888888 888      888    \n";
	cout << "Y88b. .d88P Y88b  d88P      888        888    Y88..88P  888 Y8b.     Y88b.    Y88b.  \n";
	cout << " \"Y88888P\"   \"Y8888P\"       888        888     \"Y88P\"   888  \"Y8888   \"Y8888P  \"Y888 \n";
	cout << "                                                        888                          \n";
	cout << "                                                       d88P                          \n";
	cout << "                                                     888P\"                           \n\n";


	cout << right << setw(64) << "Mini Project for Operating Systems Lab (CS255)" << "\n\n";
	cout << right << setw(49) << "Project by Group 4" << "\n\n";
	for (int i=0; i < 10; i++)
		cout << right << setw(31 + members[i].length()) << members[i] << endl;
	cout << endl << string(87, '=') << endl;

}