#include<bits/stdc++.h>
#include "include/Dining_Philosophers.h"

using namespace std;

//structure to store details of a process
struct dining_process
{
  int id,AT,BT,CT,TAT,WT;
  //AT is arrival time, BT is burst time, CT is completion time, TAT is turnarounnd time, WT is waiting time,rBT is remaining BT.
};

/*function to complete the process by updating completion time,tuenaround time and waiting time of the process*/
void dining_complete( struct dining_process *pr,int t)
{
  pr->CT=t+pr->BT;
  pr->TAT=pr->CT-pr->AT;
  pr->WT=pr->TAT-pr->BT;
}

void Dining_Philosophers() 
{
  
  int n;//to store the number of diners present;
  cout<<"    Dining-Philosophers problem :\n";  
  
  cout<<"    Enter the number of Diners : ";
  cin>>n;

  struct dining_process d[n];
  int c[n];
  int dt[n];//c[i] array is used to store when the chopstick is next available.dt[i] is used  to store when the diner will be able to dine if the unfinished diners dont dine at all. so initail value of dt[i]=d[i].AT.

  int k=0;//k used to store the number of diners that have finished dining.

  cout<<"    Enter the AT and BT of diners in order in which they are sitting around the table.\n    (Enter BT=zero if the diner dosent wish to eat) : \n";
  int i;
  for(i=0;i<n;i++)
  {
    cout<<"    AT and BT of diner "<<i<<" : ";
    cin>>d[i].AT>>d[i].BT;
    c[i]=0;
    dt[i]=d[i].AT;
    d[i].id=i+1;
    if(d[i].BT!=0)
      d[i].CT=0;
    else
    {
      d[i].CT=d[i].AT;
      d[i].TAT=0;
      d[i].WT=0;
      k++;
    }
  }

  //Note that the zero indexed chopstick is left of zero indexed diner.

  if(n==1)
  {
    d[0].CT=d[0].AT+d[0].BT;
    d[0].TAT=d[0].BT;
    d[0].WT=0;
    k=1;
  }

  while(k<n)
  {
    int idx=-1;//used to find index of diner with lowest dt value.
    for(i=0;i<n;i++)
    {
      if(!(d[i].CT!=0 && !(d[i].BT==0 && d[i].AT==d[i].CT)))
      {
        if(idx==-1)
          idx=i;
        else if(dt[i]<dt[idx])
          idx=i;
      }
    }
    //completing the dinner of the person with index idx
    dining_complete(d+idx,dt[idx]);
    k++;

    //updation related to the left chop stick
    c[idx]=d[idx].CT;
    if(idx==0)
    {
      if(d[n-1].CT==0 && c[idx]>c[n-1])
        dt[n-1]=c[idx];
    }
    else
    {
      if(d[idx-1].CT==0 && c[idx]>c[idx-1])
        dt[idx-1]=c[idx];
    }

    //updation related to the right chop stick
    if(idx==n-1)
    {
      c[0]=d[idx].CT;
      if(d[0].CT==0 && c[0]>c[1])
        dt[0]=c[0];
    }
    else
    {
      c[idx+1]=d[i].CT;
      if(idx==n-2)
      {
        if(d[n-1].CT==0 && c[n-1]>c[0])
          dt[n-1]=c[n-1];
      }
      else
      {
        if(d[idx+1].CT==0 && c[idx+1]>c[idx+2])
          dt[idx+1]=c[idx+1];
      }
    }
  }

  //printing details
  cout<<"\n";
  cout<<"    Details of Diners with columns in order of AT,BT,CT,TAT,WT.\n";
  for(i=0;i<n;i++)
  {
    cout<<"    Diner "<<i+1<<" : AT="<<d[i].AT<<" BT="<<d[i].BT<<" CT="<<d[i].CT<<" TAT="<<d[i].TAT<<" WT="<<d[i].WT<<"\n";
  }
  cout<<"\n";

  //printing time stamps.
  i=0;
  int t=0,x;
  cout<<"    printing at each timestamp :\n";
  while(i<n)
  {
    cout<<"\n    At time t="<<t<<" :\n";
    for(x=0;x<n;x++)
    {
      if(d[x].AT<=t)
      {
        if(t==d[x].CT)
        {
          cout<<"    Diner no "<<d[x].id<<" has just finished.\n";
          i++;
        }
        else if(t<d[x].CT-d[x].BT)
          cout<<"    Diner no "<<d[x].id<<" is waiting.\n";
        else if(t==d[x].CT-d[x].BT)
          cout<<"    Diner no "<<d[x].id<<" started.\n";
        else if(t<d[x].CT && t>d[x].CT-d[x].BT)
          cout<<"    Diner no "<<d[x].id<<" is processing.\n";
        else if(d[x].CT==-1)
        {
          cout<<"    Diner no "<<d[x].id<<" has been canceled due to permanent overflow.\n";
          i++;
        }
      }
    }
    t++;
  }
  cout<<"\n";
}
