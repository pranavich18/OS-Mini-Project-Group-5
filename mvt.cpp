#include<bits/stdc++.h>
#include "include/mvt.h"

using namespace std;

void mvt_first_fit(){
    struct process{
        int id=-1;
        int total_size;
        int starting;
        int ending;
    }p[100];

    vector <pair<int,int>> empty_slots;
    int memory_size;
    cout<<"Enter size of main memory ";
    cin>>memory_size;
    empty_slots.push_back(make_pair(0,memory_size));
    int choice=1;
    while(choice!=4)
    {
        cout<<"\nYou have the following choices :-\n1)Enter new process\n2)Delete an existing process\n3)Display present state of memory\n4)Exit\n";
        cout<<"Enter choice ";
        cin>>choice;
        if(choice==1){
            int i=0;
            while(p[i].id!=-1)
            i++;
            cout<<"Enter process id ";
            cin>>p[i].id;
            cout<<"Enter process size ";
            cin>>p[i].total_size;
            int min_starting=5000;
            int total_empty=0;
            for(auto a=empty_slots.begin();a!=empty_slots.end();a++)
            {
                if(p[i].total_size<=(a->second)-(a->first))
                {
                    if(min_starting>a->first)
                    {
                        min_starting=a->first;
                    }
                }
                total_empty+=(a->second)-(a->first);
            }
            if(min_starting==5000)
            {
                if(total_empty>=p[i].total_size)
                {
                    cout<<"Process cannot be accommodated due to external fragmentation"<<endl;
                }
                else cout<<"Process too large. Not enough space in memory"<<endl;
                p[i].id=-1;
                p[i].total_size=0;
                p[i].starting=0;
                p[i].ending=0;
            }
            else{
                for(auto a=empty_slots.begin();a!=empty_slots.end();a++)
                {
                    if(a->first==min_starting)
                    {
                        p[i].starting=min_starting;
                        p[i].ending=min_starting+p[i].total_size;
                        int to_be_inserted=a->second;
                        empty_slots.erase(a);
                        if(p[i].ending!=to_be_inserted)
                        {
                            empty_slots.push_back(make_pair(p[i].ending,to_be_inserted));
                        }
                        cout<<"Process inserted successfully. From "<<p[i].starting<<" To "<<p[i].ending<<endl;
                        break;
                    }
                }
            }
        }
        else if(choice == 2){
            int pid;
            cout<<"Enter process id to be deleted ";
            cin>>pid;
            int i=0;
            while(p[i].id!=pid&&i<=100)
            i++;
            if(i==101)
            {
                cout<<"Process not in memory"<<endl;
                return;
            }
            for(auto a=empty_slots.begin();a!=empty_slots.end();a++)
            {
                if(a->first==p[i].ending)
                {
                    p[i].ending=a->second;
                    empty_slots.erase(a);
                    a--;
                }
                if(a->second==p[i].starting)
                {
                    p[i].starting=a->first;
                    empty_slots.erase(a);
                    a--;
                }
                p[i].id=-1;
                p[i].total_size=0;
            }
            empty_slots.push_back(make_pair(p[i].starting,p[i].ending));
            cout<<"Process removed successfully"<<endl;

        }
        else if(choice==3){
            int count=0;
            cout<<"The processes in memory and their location are as follows :-\n";
            for(int i=0;i<100;i++)
            {
                if(p[i].id!=-1)
                {
                    cout<<"Process "<<p[i].id<<" from "<<p[i].starting<<" to "<<p[i].ending<<endl;
                    count++;
                }
            }
            if(count==0)
            cout<<"No process in memory"<<endl;
            if(empty_slots.size()==0)
            {
                cout<<"Memory completely occupied. No process can be accommodated anymore unless an existing process is deleted"<<endl;
                return;
            }
            cout<<"The empty slots in memory are "<<endl;
            for(auto a=empty_slots.begin();a!=empty_slots.end();a++)
            {
                cout<<"From "<<a->first<<" to "<<a->second<<endl;
            }
        }
        else if(choice==4){
            break;
        }
        else
            cout<<"Wrong Choice\n";
    }
    return;
}

void mvt_best_fit(){
    struct process{
        int id=-1;
        int total_size;
        int starting;
        int ending;
    }p[100];

    vector <pair<int,int>> empty_slots;
    int memory_size;
    cout<<"Enter size of main memory ";
    cin>>memory_size;
    empty_slots.push_back(make_pair(0,memory_size));
    int choice=1;
    while(choice!=4)
    {
        cout<<"\nYou have the following choices :-\n1)Enter new process\n2)Delete an existing process\n3)Display present state of memory\n4)Exit\n";
        cout<<"Enter choice ";
        cin>>choice;
        if(choice==1){
            int i=0;
            while(p[i].id!=-1)
            i++;
            cout<<"Enter process id ";
            cin>>p[i].id;
            cout<<"Enter process size ";
            cin>>p[i].total_size;
            int min_starting=5000;
            int best_size=5000;
            int total_empty=0;
            for(auto a=empty_slots.begin();a!=empty_slots.end();a++)
            {
                if(p[i].total_size<=(a->second)-(a->first))
                {
                    if(best_size>(a->second)-(a->first))
                    {
                        best_size=(a->second)-(a->first);
                        min_starting=a->first;
                    }
                    else if(best_size==(a->second)-(a->first))
                    {
                        if(min_starting>a->first)
                        min_starting=a->first;
                    }
                }
                total_empty+=(a->second)-(a->first);
            }
            if(min_starting==5000)
            {
                if(total_empty>=p[i].total_size)
                {
                    cout<<"Process cannot be accomodated due to external fragmentation"<<endl;
                }
                else cout<<"Process too large. Not enough space in memory"<<endl;
                p[i].id=-1;
                p[i].total_size=0;
                p[i].starting=0;
                p[i].ending=0;
            }
            else{
                for(auto a=empty_slots.begin();a!=empty_slots.end();a++)
                {
                    if(a->first==min_starting)
                    {
                        p[i].starting=min_starting;
                        p[i].ending=min_starting+p[i].total_size;
                        int to_be_inserted=a->second;
                        empty_slots.erase(a);
                        if(p[i].ending!=to_be_inserted)
                        {
                            empty_slots.push_back(make_pair(p[i].ending,to_be_inserted));
                        }
                        cout<<"Process inserted successfully. From "<<p[i].starting<<" To "<<p[i].ending<<endl;
                        break;
                    }
                }
            }
        }
        else if(choice == 2){
            int pid;
            cout<<"Enter process id to be deleted ";
            cin>>pid;
            int i=0;
            while(p[i].id!=pid&&i<=100)
            i++;
            if(i==101)
            {
                cout<<"Process not in memory"<<endl;
                return;
            }
            for(auto a=empty_slots.begin();a!=empty_slots.end();a++)
            {
                if(a->first==p[i].ending)
                {
                    p[i].ending=a->second;
                    empty_slots.erase(a);
                    a--;
                }
                if(a->second==p[i].starting)
                {
                    p[i].starting=a->first;
                    empty_slots.erase(a);
                    a--;
                }
                p[i].id=-1;
                p[i].total_size=0;
            }
            empty_slots.push_back(make_pair(p[i].starting,p[i].ending));
            cout<<"Process removed successfully"<<endl;

        }
        else if(choice==3){
            int count=0;
            cout<<"The processes in memory and their location are as follows :-\n";
            for(int i=0;i<100;i++)
            {
                if(p[i].id!=-1)
                {
                    cout<<"Process "<<p[i].id<<" from "<<p[i].starting<<" to "<<p[i].ending<<endl;
                    count++;
                }
            }
            if(count==0)
            cout<<"No process in memory"<<endl;
            if(empty_slots.size()==0)
            {
                cout<<"Memory completely occupied. No process can be accommodated anymore unless an existing process is deleted"<<endl;
                return;
            }
            cout<<"The empty slots in memory are "<<endl;
            for(auto a=empty_slots.begin();a!=empty_slots.end();a++)
            {
                cout<<"From "<<a->first<<" to "<<a->second<<endl;
            }
        }
        else if(choice==4){
            break;
        }
        else
            cout<<"Wrong Choice\n";
    }
    return;
}

void mvt_worst_fit(){
    struct process{
        int id=-1;
        int total_size;
        int starting;
        int ending;
    }p[100];

    vector <pair<int,int>> empty_slots;
    int memory_size;
    cout<<"Enter size of main memory ";
    cin>>memory_size;
    empty_slots.push_back(make_pair(0,memory_size));
    int choice=1;
    while(choice!=4)
    {
        cout<<"\nYou have the following choices :-\n1)Enter new process\n2)Delete an existing process\n3)Display present state of memory\n4)Exit\n";
        cout<<"Enter choice ";
        cin>>choice;
        if(choice==1){
            int i=0;
            while(p[i].id!=-1)
            i++;
            cout<<"Enter process id ";
            cin>>p[i].id;
            cout<<"Enter process size ";
            cin>>p[i].total_size;
            int min_starting=5000;
            int worst_size=-1;
            int total_empty=0;
            for(auto a=empty_slots.begin();a!=empty_slots.end();a++)
            {
                if(p[i].total_size<=(a->second)-(a->first))
                {
                    if(worst_size<(a->second)-(a->first))
                    {
                        worst_size=(a->second)-(a->first);
                        min_starting=a->first;
                    }
                    else if(worst_size==(a->second)-(a->first))
                    {
                        if(a->first<min_starting)
                        min_starting=a->first;
                    }
                }
                total_empty+=(a->second)-(a->first);
            }
            if(min_starting==5000)
            {
                if(total_empty>=p[i].total_size)
                {
                    cout<<"Process cannot be accommodated due to external fragmentation"<<endl;
                }
                else cout<<"Process too large. Not enough space in memory"<<endl;
                p[i].id=-1;
                p[i].total_size=0;
                p[i].starting=0;
                p[i].ending=0;
            }
            else{
                for(auto a=empty_slots.begin();a!=empty_slots.end();a++)
                {
                    if(a->first==min_starting)
                    {
                        p[i].starting=min_starting;
                        p[i].ending=min_starting+p[i].total_size;
                        int to_be_inserted=a->second;
                        empty_slots.erase(a);
                        if(p[i].ending!=to_be_inserted)
                        {
                            empty_slots.push_back(make_pair(p[i].ending,to_be_inserted));
                        }
                        cout<<"Process inserted successfully. From "<<p[i].starting<<" To "<<p[i].ending<<endl;
                        break;
                    }
                }
            }
        }
        else if(choice == 2){
            int pid;
            cout<<"Enter process id to be deleted ";
            cin>>pid;
            int i=0;
            while(p[i].id!=pid&&i<=100)
            i++;
            if(i==101)
            {
                cout<<"Process not in memory"<<endl;
                return;
            }
            for(auto a=empty_slots.begin();a!=empty_slots.end();a++)
            {
                if(a->first==p[i].ending)
                {
                    p[i].ending=a->second;
                    empty_slots.erase(a);
                    a--;
                }
                if(a->second==p[i].starting)
                {
                    p[i].starting=a->first;
                    empty_slots.erase(a);
                    a--;
                }
                p[i].id=-1;
                p[i].total_size=0;
            }
            empty_slots.push_back(make_pair(p[i].starting,p[i].ending));
            cout<<"Process removed successfully"<<endl;

        }
        else if(choice==3){
            int count=0;
            cout<<"The processes in memory and their location are as follows :-\n";
            for(int i=0;i<100;i++)
            {
                if(p[i].id!=-1)
                {
                    cout<<"Process "<<p[i].id<<" from "<<p[i].starting<<" to "<<p[i].ending<<endl;
                    count++;
                }
            }
            if(count==0)
            cout<<"No process in memory"<<endl;
            if(empty_slots.size()==0)
            {
                cout<<"Memory completely occupied. No process can be accommodated anymore unless an existing process is deleted"<<endl;
                return;
            }
            cout<<"The empty slots in memory are "<<endl;
            for(auto a=empty_slots.begin();a!=empty_slots.end();a++)
            {
                cout<<"From "<<a->first<<" to "<<a->second<<endl;
            }
        }
        else if(choice==4){
            break;
        }
        else
            cout<<"Wrong Choice\n";
    }
    return;
}

void mvt(){
    cout<<"Enter the choice for Variable Partitioning Algorithms\n 1 for First Fit\n 2 for Best Fit\n 3 for Worst Fit\n 4 for Exit\n";
    int ch=0;
    while(ch!=4){
        cout<<"Enter you choice:\n";
        cin>>ch;
        if(ch==1){
            mvt_first_fit();
        }
        else if(ch==2){
            mvt_best_fit();
        }
        else if(ch==3){
            mvt_worst_fit();
        }
        else if(ch==4)
            break;
        else
            cout<<"Wrong Choice!!\n";
    }
    return;
}
