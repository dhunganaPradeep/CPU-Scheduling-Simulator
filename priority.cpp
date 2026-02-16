#include<iostream>
#include "header files/priority.h"
using namespace std;

// priority scheduling - lower number = higher priorit

void prioritySched(int proc[],int bt[],int prio[],int n)
{
    int wt[100],tat[100];

    // copies of proc, bt, and prio 
    int p[100], b[100], pr[100];
    for(int i=0;i<n;i++){
        p[i] = proc[i];
        b[i] = bt[i];
        pr[i] = prio[i];
    }

    // using bubble sort by priority (ascending = lower number means higher priority) easy that's why its not fast tho 
    for(int i=0;i<n-1;i++)
    {
        for(int j=0;j<n-i-1;j++)
        {
            if(pr[j] > pr[j+1])
            {
                int temp = pr[j];
                pr[j] = pr[j+1];
                pr[j+1] = temp;

                temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;

                temp = b[j];
                b[j] = b[j+1];
                b[j+1] = temp;
            }
        }
    }

    // after sorting its basically fcfs
    // first process wt is 0
    wt[0] = 0;
    for(int i=1;i<n;i++)
        wt[i] = wt[i-1] + b[i-1];

    // tat = wt + bt
    for(int i=0;i<n;i++)
        tat[i] = wt[i] + b[i];

    float totalWt=0,totalTat=0;

    cout<<"\n";
    cout<<"P\tPri\tWT\tTAT"<<endl;
    cout<<"-----------------------------"<<endl;
    for(int i=0;i<n;i++)
    {
        cout<<p[i]<<"\t"<<pr[i]<<"\t"<<wt[i]<<"\t"<<tat[i]<<endl;
        totalWt += wt[i];
        totalTat += tat[i];
    }
    
    cout<<"\nAvg WT  = "<<totalWt/n<<endl;
    cout<<"Avg TAT = "<<totalTat/n<<endl;

    cout<<"\nTimeline:\n";

    cout<<" ";
    for(int i=0;i<n;i++){
        for(int j=0;j<b[i];j++) cout<<"--";
        cout<<" ";
    }
    cout<<endl;

    cout<<"|";
    for(int i=0;i<n;i++){
        int spaces = b[i];
        for(int j=0;j<spaces-1;j++) cout<<" ";
        cout<<"P"<<p[i];
        for(int j=0;j<spaces-1;j++) cout<<" ";
        cout<<"|";
    }
    cout<<endl;

    cout<<" ";
    for(int i=0;i<n;i++){
        for(int j=0;j<b[i];j++) cout<<"--";
        cout<<" ";
    }
    cout<<endl;

    // time markers
    cout<<"0";
    int time=0;
    for(int i=0;i<n;i++){
        time += b[i];
        for(int j=0;j<b[i]*2-1;j++) cout<<" ";
        if(time<10) cout<<" ";
        cout<<time;
    }
    cout<<endl;
}
