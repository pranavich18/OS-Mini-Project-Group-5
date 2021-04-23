#include<bits/stdc++.h>
#include "include/Disk_Scheduling.h"

using namespace std;


void Disk_Scheduling()
{
  while(1)
  {
    int choice;
    cout<<"    Enter 0.Main Menu 1.SCAN 2.CSCAN 3.LOOK 4.CLOOK 5.SSTF 6.FCFS : ";
    cin>>choice;
    if(choice<1 || choice>6)
    {
      cout<<"    Returning to main menu\n\n";
      return;
    }

    else
    {
      int tot_disks, n;//n is the number of requests.
      cout<<"    No. of cylinders in disk : ";
      cin>>tot_disks;
      cout<<"    No. of disk access requests : ";
      cin>>n;
      int req[n];
      int cur_pos, cur_dir;

      int i;
      cout<<"    Enter the request array :\n    ";
      int flag=0;
      for(i=0; i<n; i++)
      {
        cin>>req[i];
      }
      for(i=0; i<n; i++)
      {
        if(req[i]>=tot_disks || req[i]<0)
        {
          cout<<"    "<<req[i]<<" is invalid disk request. disk scheduling aborted.\n";
          flag=1;
        }
      }
      if(flag==1)
      {
        cout<<"\n";
        continue;
      }
      while(1)
      {
        cout<<"    Enter current position of R/W head : ";
        cin>>cur_pos;
        if(cur_pos<0 || cur_pos>=tot_disks)
        {
          cout<<"    Invalid position of R/W head.\n";
        }
        else
        {
          break;
        }
      }
      while(1)
      {
        cout<<"    Enter current direction of R/W head(0=left, 1=right) : ";
        cin>>cur_dir;
        if(cur_dir==0 || cur_dir==1)
        {
          break;
        }
        else
        {
          cout<<"    Invalid direction of R/W head.\n";
        }
      }

      int seek_time=0;
      if(choice==1)
      {
        sort(req, req+n);
        int mark;


        if(cur_dir==1)
        {
          for(mark=0; mark<n; mark++)
          {
            if(cur_pos<=req[mark])
            {
              break;
            }
          }

          cout<<"    Seek Sequence :";
          for(i=mark; i<n; i++)
          {
            cout<<" "<<req[i];
          }
          if(req[n-1]!=tot_disks-1 && mark!=0)
          cout<<" "<<tot_disks-1;
          for(i=mark-1; i>=0; i--)
          {
            cout<<" "<<req[i];
          }

          if(mark!=0)
          {
            seek_time=(tot_disks-1-cur_pos)+(tot_disks-1-req[0]);
          }
          else
          {
            seek_time=req[n-1]-cur_pos;
          }
        }
        else if(cur_dir==0)
        {
          for(mark=0; mark<n; mark++)
          {
            if(cur_pos<req[mark])
            {
              break;
            }
          }
          cout<<"    Seek Sequence :";
          for(i=mark-1; i>=0; i--)
          {
            cout<<" "<<req[i];
          }
          if(req[0]!=0 && mark!=n)
          cout<<" "<<0;
          for(i=mark; i<n; i++)
          {
            cout<<" "<<req[i];
          }

          if(mark!=n)
          {
            seek_time=(cur_pos)+(req[n-1]);
          }
          else
          {
            seek_time=cur_pos-req[0];
          }
        }
        cout<<"\n";


      }
      else if(choice==2)
      {
        sort(req, req+n);
        int mark;

        if(cur_dir==1)
        {
          for(mark=0; mark<n; mark++)
          {
            if(cur_pos<=req[mark])
            {
              break;
            }
          }

          cout<<"    Seek Sequence :";
          for(i=mark; i<n; i++)
          {
            cout<<" "<<req[i];
          }
          if(mark!=0)
          {
            if(req[n-1]!=tot_disks-1)
            cout<<" "<<tot_disks-1;
            if(req[0]!=0)
            cout<<" "<<0;
          }
          for(i=0; i<mark; i++)
          {
            cout<<" "<<req[i];
          }

          if(mark!=0)
          {
            seek_time=(tot_disks-1-cur_pos)+(tot_disks-1)+(req[mark-1]);
          }
          else
          {
            seek_time=req[n-1]-cur_pos;
          }
        }
        else if(cur_dir==0)
        {
          for(mark=0; mark<n; mark++)
          {
            if(cur_pos<req[mark])
            {
              break;
            }
          }

          cout<<"    Seek Sequence :";
          for(i=mark-1; i>=0; i--)
          {
            cout<<" "<<req[i];
          }
          if(mark!=n)
          {
            if(req[0]!=0)
            cout<<" "<<0;
            if(req[n-1]!=tot_disks-1)
            cout<<" "<<tot_disks-1;
          }
          for(i=n-1; i>=mark; i--)
          {
            cout<<" "<<req[i];
          }

          if(mark!=n)
          {
            seek_time=(cur_pos)+(tot_disks-1)+(tot_disks-1-req[mark]);
          }
          else
          {
            seek_time=cur_pos-req[0];
          }
        }
        cout<<"\n";

      }
      else if(choice==3)
      {
        sort(req, req+n);
        int mark;

        if(cur_dir==1)
        {
          for(mark=0; mark<n; mark++)
          {
            if(cur_pos<=req[mark])
            {
              break;
            }
          }

          cout<<"    Seek Sequence :";
          for(i=mark; i<n; i++)
          {
            cout<<" "<<req[i];
          }
          for(i=mark-1; i>=0; i--)
          {
            cout<<" "<<req[i];
          }

          if(mark!=0)
          {
            seek_time=abs(req[n-1]-cur_pos)+(req[n-1]-req[0]);
          }
          else
          {
            seek_time=req[n-1]-cur_pos;
          }
        }
        else if(cur_dir==0)
        {
          for(mark=0; mark<n; mark++)
          {
            if(cur_pos<req[mark])
            {
              break;
            }
          }

          cout<<"    Seek Sequene :";
          for(i=mark-1; i>=0; i--)
          {
            cout<<" "<<req[i];
          }
          for(i=mark; i<n; i++)
          {
            cout<<" "<<req[i];
          }

          if(mark!=n)
          {
            seek_time=abs(cur_pos-req[0])+(req[n-1]-req[0]);
          }
          else
          {
            seek_time=(cur_pos-req[0]);
          }
        }
        cout<<"\n";

      }
      else if(choice==4)
      {
        sort(req, req+n);
        int mark;

        if(cur_dir==1)
        {
          for(mark=0; mark<n; mark++)
          {
            if(cur_pos<=req[mark])
            {
              break;
            }
          }

          cout<<"    Seek Sequence :";
          for(i=mark; i<n; i++)
          {
            cout<<" "<<req[i];
          }
          for(i=0; i<mark; i++)
          {
            cout<<" "<<req[i];
          }

          if(mark!=0)
          {
            seek_time=abs(req[n-1]-cur_pos)+(req[n-1]-req[0])+(req[mark-1]-req[0]);
          }
          else
          {
            seek_time=req[n-1]-cur_pos;
          }
        }
        else if(cur_dir==0)
        {
          for(mark=0; mark<n; mark++)
          {
            if(cur_pos<req[mark])
            {
              break;
            }
          }

          cout<<"    Seek Sequence :";
          for(i=mark-1; i>=0; i--)
          {
            cout<<" "<<req[i];
          }
          for(i=n-1; i>=mark; i--)
          {
            cout<<" "<<req[i];
          }

          if(mark!=n)
          {
            seek_time=abs(cur_pos-req[0])+(req[n-1]-req[0])+(req[n-1]-req[mark]);
          }
          else
          {
            seek_time=cur_pos-req[0];
          }
        }
        cout<<"\n";
      }
      else if(choice==5)
      {
        sort(req, req+n);

        cout<<"    Seek Sequence :";
        if(cur_pos<=req[0])
        {
          for(i=0; i<n; i++)
          {
            cout<<" "<<req[i];
            seek_time+=abs(req[i]-cur_pos);
            cur_pos=req[i];
          }
        }
        else if(req[n-1]<=cur_pos)
        {
          for(i=n-1; i>=0; i--)
          {
            cout<<" "<<req[i];
            seek_time+=abs(req[i]-cur_pos);
            cur_pos=req[i];
          }
        }
        else
        {
          int mark;
          for(mark=0; mark<n-1; mark++)
          {
            if(req[mark]==cur_pos)
            {
              cout<<" "<<req[mark];
              if(req[mark+1]-cur_pos>=cur_pos-req[mark-1])
              {
                for(i=mark+1; i<n; i++)
                {
                  cout<<" "<<req[i];
                  seek_time+=abs(req[i]-cur_pos);
                  cur_pos=req[i];
                }
                for(i=mark-1; i>=0; i--)
                {
                  cout<<" "<<req[i];
                  seek_time+=abs(req[i]-cur_pos);
                  cur_pos=req[i];
                }
              }
              else
              {
                for(i=mark-1; i>=0; i--)
                {
                  cout<<" "<<req[i];
                  seek_time+=abs(req[i]-cur_pos);
                  cur_pos=req[i];
                }
                for(i=mark+1; i<n; i++)
                {
                  cout<<" "<<req[i];
                  seek_time+=abs(req[i]-cur_pos);
                  cur_pos=req[i];
                }
              }
              break;
            }
            else if(req[mark]<cur_pos && cur_pos<req[mark+1])
            {
              if(req[mark+1]-cur_pos<=cur_pos-req[mark])
              {
                for(i=mark+1; i<n; i++)
                {
                  cout<<" "<<req[i];
                  seek_time+=abs(req[i]-cur_pos);
                  cur_pos=req[i];
                }
                for(i=mark; i>=0; i--)
                {
                  cout<<" "<<req[i];
                  seek_time+=abs(req[i]-cur_pos);
                  cur_pos=req[i];
                }
              }
              else
              {
                for(i=mark; i>=0; i--)
                {
                  cout<<" "<<req[i];
                  seek_time+=abs(req[i]-cur_pos);
                  cur_pos=req[i];
                }
                for(i=mark+1; i<n; i++)
                {
                  cout<<" "<<req[i];
                  seek_time+=abs(req[i]-cur_pos);
                  cur_pos=req[i];
                }
              }
              break;
            }
          }
        }
        cout<<"\n";

      }
      else if(choice==6)
      {
        cout<<"    Seek Sequence :";
        for(i=0; i<n; i++)
        {
          cout<<" "<<req[i];
          seek_time+=abs(req[i]-cur_pos);
          cur_pos=req[i];
        }
        cout<<"\n";
      }

      cout<<"    Seek Time = "<<seek_time<<"\n\n";
    }

  }
}
