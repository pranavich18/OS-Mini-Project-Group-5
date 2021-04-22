#include<stdio.h>
#include<stdlib.h>

struct producer{
    int p;
    int num;
    int p_or_c;
    int arr;
    int bur;
    int com;
};

void sort(struct producer *u,int n)
{
    int i,j;
    for(i=0;i<n;i++)
    {
        for(j=i+1;j<=n;j++)
        {
            if(u[i].arr>u[j].arr || (u[i].arr==u[j].arr && u[i].p_or_c<u[j].p_or_c))
            {
                struct producer temp;
                temp=u[i];
                u[i]=u[j];
                u[j]=temp;
            }
        }
    }
}
void swap(struct producer *a,struct producer *b)
{
    struct producer *temp;
    temp=a;
    a=b;
    b=temp;
}
void producer_consumer()
{
    printf("\tPRODUCER CONSUMER PROBLEM\n-------\n");
    int buffer,prod_cnt,cons_cnt,time=0,bar=0;
    int i,j;
    printf("Enter the buffer time\t:");
    scanf("%d",&buffer);
    printf("Enter the number of producers\t:");
    scanf("%d",&prod_cnt);
    printf("Enter the number of consumers\t:");
    scanf("%d",&cons_cnt);
    struct producer user[prod_cnt+cons_cnt];
    
    for(i=0;i<prod_cnt+cons_cnt;i++)
    {
        user[i].num=i+1;
        if(i<prod_cnt)
        {
            user[i].p_or_c=1;
            user[i].p=i+1;
            printf("Producer %d\t",i+1);
            printf("Enter the arrival time \t:");
            scanf("%d",&user[i].arr);
            printf("Enter the burst time \t: ");
            scanf("%d",&user[i].bur);
        }
        else
        {
            user[i].p_or_c=0;
            user[i].p=i+1-prod_cnt;
            printf("Consumer %d : ",i+1-prod_cnt);
            printf("Enter the arrival time \t:");
            scanf("%d",&user[i].arr);
            printf("Enter the burst time \t:");
            scanf("%d",&user[i].bur);
        }
    }
    printf("--------------------------------------------\n");
    sort(user,prod_cnt+cons_cnt);
    int total = prod_cnt+cons_cnt;
    for(i=0;i<total;i++)
    {
        if(prod_cnt==0 && cons_cnt>0 && bar ==0)
        {
            printf("Consumer cannot consume since the bar is empty and there are no producers to produce\n");
            printf("UNDERFLOW\n");
            break;
        }
        if(cons_cnt==0 && prod_cnt>0 && bar==buffer)
        {
            printf("Producer cannot produce since the bar is of full capacity and there are no consumers  to consume\n");
            printf("OVERFLOW\n");
            break;
        }
        if(user[i].arr<=time && user[i].p_or_c==0 && bar == 0)
        {
            for(j=i+1;j<total;j++)
            {
                while(user[j].p_or_c==0)
                {
                    swap(&user[i],&user[j]);
                }
                break;
            }
        }
        if(user[i].arr<=time && user[i].p_or_c==1 && bar == buffer)
        {
            for(j=i+1;j<total;j++)
            {
                while(user[j].p_or_c==1)
                {
                    swap(&user[i],&user[j]);
                }
                break;
            }
        }
        if(user[i].arr<=time)
        {
            time=time+user[i].bur;
        }
        else
        {
            time=user[i].arr+user[i].bur;
        }
        user[i].com=time;
        if(user[i].p_or_c==1)
        {
            bar++;
            prod_cnt--;
        }
        else
        {
            bar--;
            cons_cnt--;
        }
    }
    i=0;
    while(i<=time)
    {
        printf("At Time %d:\n",i);
        for(j=0;j<total;j++)
        {
            if(user[j].arr==i && user[j].p_or_c==1)
            {
                printf("Producer %d has arrived\n",user[j].p);
            }
            if(user[j].arr==i && user[j].p_or_c==0)
            {
                printf("Consumer %d has arrived\n",user[j].p);
            }
            if(user[j].arr<=i && (user[j].com-user[j].bur)>i && user[j].p_or_c==1)
            {
                printf("Producer %d is waiting\n",user[j].p);
            }
            if(user[j].arr<=i && (user[j].com-user[j].bur)>i && user[j].p_or_c==0)
            {
                printf("Consumer %d is waiting\n",user[j].p);
            }
            if(user[j].arr<=i && (user[j].com-user[j].bur)<=i && i<=user[j].com && user[j].p_or_c==1)
            {
                printf("Producer %d is producing\n",user[j].p);
            }
            if(user[j].arr<=i && (user[j].com-user[j].bur)<=i && i<=user[j].com && user[j].p_or_c==0)
            {
                printf("Consumer %d is consuming\n",user[j].p);
            }
        }
        printf("\n");i++;
    }
}
