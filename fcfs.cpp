#include<iostream>
#include "fcfs.h"
using namespace std;

// fcfs is basically whoever comes first gets the cpu first
void fcfs(int proc[],int bt[],int n)
{
    int wt[100], tat[100];
    wt[0] = 0; //first process ko waiting time 0
    // waiting time = previous process wt + previous burst time
    for(int i=1;i<n;i++)
    {
        wt[i] = wt[i-1] + bt[i-1];
    }

    // turnaround = waiting + burst
    for(int i=0;i<n;i++){
        tat[i] = wt[i] + bt[i];
    }

    float totalWt=0, totalTat=0;

    cout<<"\n";
    cout<<"P\tWT\tTAT"<<endl;
    cout<<"-------------------"<<endl;
    for(int i=0;i<n;i++)
    {
        cout<<proc[i]<<"\t"<<wt[i]<<"\t"<<tat[i]<<endl;
        totalWt += wt[i];
        totalTat += tat[i];
    }

    cout<<"\nAvg WT  = "<<totalWt/n<<endl;
    cout<<"Avg TAT = "<<totalTat/n<<endl;

    // just showing which process runs when
    cout<<"\nTimeline:\n";

    cout<<" ";
    for(int i=0;i<n;i++){
        for(int j=0;j<bt[i];j++) cout<<"--";
        cout<<" ";
    }
    cout<<endl;

    cout<<"|";
    for(int i=0;i<n;i++){
        int spaces = bt[i];
        for(int j=0;j<spaces-1;j++) cout<<" ";
        cout<<"P"<<proc[i];
        for(int j=0;j<spaces-1;j++) cout<<" ";
        cout<<"|";
    }
    cout<<endl;

    cout<<" ";
    for(int i=0;i<n;i++){
        for(int j=0;j<bt[i];j++) cout<<"--";
        cout<<" ";
    }
    cout<<endl;

    cout<<"0";
    int time=0;
    for(int i=0;i<n;i++){
        time += bt[i];
        for(int j=0;j<bt[i]*2-1;j++) cout<<" ";
        if(time<10) cout<<" ";
        cout<<time;
    }
    cout<<endl;
}
