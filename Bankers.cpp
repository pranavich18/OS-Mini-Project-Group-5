#include<bits/stdc++.h>
#include "include/Bankers.h"
using namespace std;

void bankers()
{
	int resources,processes;
	
	cout<<"Enter the number of resources : ";
	cin>>resources;
	
	// stores the available and the max resources
	int available[resources], maxAvailable[resources];
	// condition to check if any process has need more than the available resource
	bool overflow = false;
	
	// input details
	for(int i = 0; i < resources;i++)
	{
		cout<<"Enter the max available instances of resource "<<i<<" : ";
		cin>>maxAvailable[i];
		available[i] = maxAvailable[i];
	}
	cout<<"Enter the number of processes : ";
	cin>>processes;
	
	cout<<endl;
	
	int need[processes][resources], alloted[processes][resources];
	bool done[processes] = {false};
	
	
	for(int i = 0;i< processes;i++)
	{
		cout<<"PROCESS " <<i<<endl;
		for(int j = 0; j < resources;j++)
		{
			cout<<"Enter the max need of resource "<<j<<" : ";
			cin>>need[i][j];
			// checking overflow condition
			if(need[i][j] > maxAvailable[j])
				overflow = true;
		}
		
		for(int j = 0; j < resources;j++)
		{
			cout<<"Enter allotated instances of resource "<<j<<" : ";
			cin>>alloted[i][j];
			// decrement the available resource by the alloted resource
			available[j] -= alloted[i][j];
			
		}
	}
	// print overflow message
	if(overflow)
	{
		 cout<<"Inputs are invalid, max need of resources are more than the max available resources"<<endl;
		 return ;
	}
	// check if the alloted resources are more than the available resources and print invalid message
	for(int i = 0; i< resources; i++)
	{
		if(available[i] < 0)
		{
			cout<<"Inputs are invalid. Sum of alloted resources are more than the max available resources"<<endl;
			return ;
		}
	}
	
	cout<<"Inputs are valid"<<endl;
	vector<int> order;
	// condition to check for deadlock
	bool deadlock = false;
	int count = 0;
	
	// continue until all process have finished or we have reached a deadlock
	while(!deadlock && count < processes)
	{
		deadlock = true;
		
		// iterate through the processes sequentially
		for(int i = 0; i < processes;i++)
		{
			// if process is already completed, continue
			if(done[i])
			 continue;
			// check if process can be executed with the available resources
			int j = 0;
			while(need[i][j] - alloted[i][j] <= available[j] && j < resources)
			{
				j++;
			}
			
			// if process is completed
			if(j == resources)
			{
				done[i] = true;
				// increment the available resources by freeing the alloted resource from the process
				for(int k = 0; k < resources; k++)
				{
					available[k] += alloted[i][k];
				}
				// deadlock hasn't occurred in the iteration
				deadlock = false;
				// push the process to the order of execution
				order.push_back(i);
				count++;
			}
		}
	}
	// print deadlock condition
	if(deadlock)
	{
		cout<<"Deadlock has occurred. It is an unsafe condition."<<endl;
	}
	else
	{
		// print the order of execution
		cout<<"It is a safe condition."<<endl;
		cout<<"The order of process execution is "<<endl;
		for(int i = 0; i < processes - 1;i++)
		{
			cout<<"Process "<<order[i]<<" -> ";
		}
		cout<<"Process "<<order[processes-1]<<endl;
	}

}