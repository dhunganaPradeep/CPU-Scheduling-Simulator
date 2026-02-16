#include<iostream>
#include "header files/roundrobin.h"
using namespace std;

// round robin - each process gets a time slice (quantum)
// if its not done it goes back to the queue

void roundRobin(int proc[],int bt[],int n,int q)
{
    int wt[100],tat[100];
    int rem[100]; // remaining burst time for each process

    // first copy the burst times
    // we need originals later for tat calculation
    for(int i=0;i<n;i++)
        rem[i] = bt[i];

    int t=0; // current time

    // for the timeline chart i need to store the order
    // each time a process runs i save its id and how long it ran
    int timeline_proc[500], timeline_time[500];
    int tl_count = 0;

    // keep going until all processes are done
    // the flag checks if theres anything left
    int done = 0;
    while(done != 1)
    {
        done = 1;
        for(int i=0;i<n;i++)
        {
            if(rem[i] > 0)
            {
                done = 0;

                if(rem[i] > q)
                {
                    // process runs for quantum time
                    timeline_proc[tl_count] = proc[i];
                    timeline_time[tl_count] = q;
                    tl_count++;

                    t += q;
                    rem[i] -= q;
                }
                else
                {
                    // process finishes in this round
                    timeline_proc[tl_count] = proc[i];
                    timeline_time[tl_count] = rem[i];
                    tl_count++;

                    t += rem[i];

                    // waiting time = current time - burst time
                    // total time spent = t, burst was bt[i]
                    // so waiting = t - bt[i]
                    wt[i] = t - bt[i];
                    rem[i] = 0;
                }
            }
        }
    }

    // tat is just wt + bt as always
    for(int i=0;i<n;i++)
        tat[i] = wt[i] + bt[i];
    float totalWt=0, totalTat=0;

    cout<<"\n";
    cout<<"P\tWT\tTAT"<<endl;
    cout<<"-------------------"<<endl;
    for(int i=0;i<n;i++)
    {
        cout<<proc[i]<<"\t"<<wt[i]<<"\t"<<tat[i]<<endl;
        totalWt+=wt[i];
        totalTat+=tat[i];
    }

    cout<<"\nAvg WT  = "<<totalWt/n<<endl;
    cout<<"Avg TAT = "<<totalTat/n<<endl;
    cout<<"\nTimeline:\n";

    cout<<" ";
    for(int i=0;i<tl_count;i++){
        for(int j=0;j<timeline_time[i];j++) cout<<"--";
        cout<<" ";
    }
    cout<<endl;

    cout<<"|";
    for(int i=0;i<tl_count;i++){
        int spaces = timeline_time[i];
        for(int j=0;j<spaces-1;j++) cout<<" ";
        cout<<"P"<<timeline_proc[i];
        for(int j=0;j<spaces-1;j++) cout<<" ";
        cout<<"|";
    }
    cout<<endl;

    cout<<" ";
    for(int i=0;i<tl_count;i++){
        for(int j=0;j<timeline_time[i];j++) cout<<"--";
        cout<<" ";
    }
    cout<<endl;

    cout<<"0";
    int ctime=0;
    for(int i=0;i<tl_count;i++){
        ctime += timeline_time[i];
        for(int j=0;j<timeline_time[i]*2-1;j++) cout<<" ";
        if(ctime<10) cout<<" ";
        cout<<ctime;
    }
    cout<<endl;
}
