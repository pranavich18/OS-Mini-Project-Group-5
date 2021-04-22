#include<bits/stdc++.h>
#include "include/sleeping_barber.h"

using namespace std;
void sleeping_barber()
{
	int barber = 0, customers,occupied = 0;
	
	cout<<"Enter the number of customers : ";
	cin>>customers;
	
	int chairs;
	cout<<"Enter the number of chairs : ";
	cin>>chairs;
	
	pair<int,int> arrival[customers];
	int burst[customers];
	
	for(int i= 0; i < customers; i++)
	{
		cout<<"Enter the arrival time of customer"<<i<<" : ";
		cin>>arrival[i].first;
		
		cout<<"Enter the burst time( time taken for haircut) of customer"<<i<<" : ";
		cin>>burst[i];
		
		arrival[i].second = i;
	}
	
	sort(arrival, arrival + customers);
	
	set<tuple<int,int,int>> event;
	
	for(auto it : arrival)
	 event.insert(make_tuple(it.first,1,it.second));


	
	queue<int> q;
	
	cout<<"Barber arrives to work and starts sleeping"<<endl;
	while(!event.empty())
	{
		auto it = (*event.begin());
		event.erase(event.begin());
		
		if(get<1>(it) == 1)
		{
			if(occupied == chairs && barber == 1)
			{
				cout<<"At time "<<get<0>(it)<<", customer"<<get<2>(it)<<" leaves because there are no empty chairs"<<endl;
			}
			else if( barber == 0)
			{
				cout<<"At time "<<get<0>(it)<<", customer"<<get<2>(it)<<" wakes barber and starts haircut"<<endl;
				barber = 1;
				event.insert(make_tuple(get<0>(it) + burst[get<2>(it)], 0, get<2>(it)));
			}
			else if(occupied < chairs && barber == 1)
			{
				cout<<"At time "<<get<0>(it)<<", customer"<<get<2>(it)<<" occupies an empty chair"<<endl;
				occupied++;
				q.push(get<2>(it));
			}
		}
		else
		{
			if(q.empty())
			{
				cout<<"At time "<<get<0>(it)<<", customer"<<get<2>(it)<<" finishes haircut and ";
				cout<<"Barber starts sleeping"<<endl;
				barber = 0;
			}
			else
			{
				occupied--;
				auto top = q.front();
				q.pop();
				
				cout<<"At time "<<get<0>(it)<<", customer"<<get<2>(it)<<" finishes haircut and ";
				cout<<" customer"<<top<<" starts haircut"<<endl;
				event.insert(make_tuple(get<0>(it) + burst[top], 0, top));
			}
		}
	}
}
				
		
