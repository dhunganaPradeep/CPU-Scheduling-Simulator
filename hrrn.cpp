#include<iostream>
#include "header files/hrrn.h"
using namespace std;

// HRRN - Highest Response Ratio Next
// non preemptive, picks the process with the highest response ratio
// response ratio = (wt + bt) / bt
// so if a process waited a long time it gets priority
// this avoids starvation which sjf has

void hrrn(int proc[],int bt[],int n)
{
    int wt[100],tat[100];
    int done[100]; // to track which ones are finished
    int order[100]; // order in which processes run

    for(int i=0;i<n;i++) done[i]=0;

    int t=0; // current time

    for(int k=0;k<n;k++)
    {
        // find process with highest response ratio
        float maxRR = -1;
        int idx = -1;

        for(int i=0;i<n;i++)
        {
            if(done[i]==0)
            {
                // waiting time for this process so far
                float w = t;
                // response ratio formula
                float rr = (w + bt[i]) / (float)bt[i];

                if(rr > maxRR)
                {
                    maxRR = rr;
                    idx = i;
                }
            }
        }

        // run this process
        order[k] = idx;
        wt[idx] = t;
        t += bt[idx];
        tat[idx] = t;
        done[idx] = 1;
    }

    float totalWt=0,totalTat=0;
    cout<<"\n";
    cout<<"P\tBT\tWT\tTAT"<<endl;
    cout<<"-----------------------------"<<endl;
    for(int i=0;i<n;i++)
    {
        cout<<proc[i]<<"\t"<<bt[i]<<"\t"<<wt[i]<<"\t"<<tat[i]<<endl;
        totalWt+=wt[i];
        totalTat+=tat[i];
    }

    cout<<"\nAvg WT  = "<<totalWt/n<<endl;
    cout<<"Avg TAT = "<<totalTat/n<<endl;

    cout<<"\nTimeline:\n";
    cout<<" ";
    for(int i=0;i<n;i++){
        int idx=order[i];
        for(int j=0;j<bt[idx];j++) cout<<"--";
        cout<<" ";
    }
    cout<<endl;

    cout<<"|";
    for(int i=0;i<n;i++){
        int idx=order[i];
        int spaces=bt[idx];
        for(int j=0;j<spaces-1;j++) cout<<" ";
        cout<<"P"<<proc[idx];
        for(int j=0;j<spaces-1;j++) cout<<" ";
        cout<<"|";
    }
    cout<<endl;

    cout<<" ";
    for(int i=0;i<n;i++){
        int idx=order[i];
        for(int j=0;j<bt[idx];j++) cout<<"--";
        cout<<" ";
    }
    cout<<endl;

    cout<<"0";
    int ctime=0;
    for(int i=0;i<n;i++){
        int idx=order[i];
        ctime+=bt[idx];
        for(int j=0;j<bt[idx]*2-1;j++) cout<<" ";
        if(ctime<10) cout<<" ";
        cout<<ctime;
    }
    cout<<endl;
}
