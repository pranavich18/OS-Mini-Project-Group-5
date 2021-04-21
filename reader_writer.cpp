#include<bits/stdc++.h>


using namespace std;

// print message based on the index of the process waiting and the index of the process running
void print_message(int id1, int id2, int index1, int index2, int time)
{
	printf("At time %d, ",time);
	if(!id1)
	cout<<"Writer";
	else
	cout<<"Reader";
	
	cout<<index1<<" has to wait as ";
	
	if(!id2)
	cout<<"Writer"<<index2<<" is writing"<<endl;
	else
	cout<<"Reader"<<index2<<" is reading"<<endl;
}


int main(){
	
	int readers, writers;
	
	cout<<"Enter the number of readers and consumers"<<endl;
	cin>>readers>>writers;
	
	// stores the details of all the processes
	vector<tuple<int,int,int,int> > processes;
	// stores whether a process has been completed 
	bool done[readers+writers] = {0};
	
	// input all the details
	cout<<"Enter the arrival time and burst time of the readers"<<endl;
	
	for(int i = 0; i < readers; i++)
	{
		int arrival, burst;
		cin>>arrival>>burst;
		processes.push_back(make_tuple(arrival,1,burst,i+1));
	}
	
	cout<<"Enter the arrival time and burst time of the writers"<<endl;
	for(int i = 0; i < writers; i++)
	{
		int arrival, burst;
		cin>>arrival>>burst;
		processes.push_back(make_tuple(arrival,0,burst,i+1));
	}
	
	// sort all the processes based on their arrival time with preference to writers
	sort(processes.begin(),processes.end());
	
	int time = 0; // current time
	int current = 0, waiting = 1;  // process running and the process waiting
	
	while(current < readers+writers)
	{
		auto top = processes[current];
		
		// if process has already been completed
		if(done[current])
		{
			current++;
			continue;
		}
		
		// make current time as arrival time if current time is less than arrival time
		if(time < get<0>(top))
		 time = get<0>(top);
		 
		// increment time with the burst time of the process
		time+=get<2>(top);
		
		// check the waiting messages
		while(get<0>(processes[waiting]) < time && waiting < readers + writers)
		{
			// if a writer is running, every other process has to wait
			if(get<1>(top) == 0)
			{
				print_message(get<1>(processes[waiting]),get<1>(top),get<3>(processes[waiting]),get<3>(top),get<0>(processes[waiting]));
				waiting++;
			}
			// if a reader is running, other readers can be allowed but not writers
			else
			{
				// make the writer wait
				if(get<1>(processes[waiting]) == 0)
				{
					print_message(get<1>(processes[waiting]),get<1>(top),get<3>(processes[waiting]),get<3>(top),get<0>(processes[waiting]));
					waiting++;
				}
				else
				{
					// allow the reader
					done[waiting] = true;
					time = max(time,get<2>(processes[waiting]) + get<0>(processes[waiting])); 
					waiting++;
				}
			}
					
		}
		
		done[current] = true;
		current++;
	}
}
