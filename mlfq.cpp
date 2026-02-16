#include<iostream>
#include "header files/mlfq.h"
using namespace std;

// MLFQ - Multi Level Feedback Queue
// 3 queues with different quantum sizes
// Q1 (quantum=4), Q2 (quantum=8), Q3 (FCFS - runs till done)
// process starts in Q1, if not done it goes to Q2, then Q3
// this is a simplified version without aging or priority boost

void mlfq(int proc[],int bt[],int n)
{
    int wt[100],tat[100],rem[100];
    int timeline_proc[500],timeline_time[500];
    int tl_count=0;

    // which queue each process is in (1, 2, or 3)
    int queue[100];

    int q1=4; // quantum for queue 1
    int q2=8; // quantum for queue 2
    // queue 3 is fcfs so no quantum

    for(int i=0;i<n;i++){
        rem[i]=bt[i];
        queue[i]=1; // everyone starts in queue 1
    }

    int t=0;
    int completed=0;

    // keep going through the queues until everything is done
    // do Q1 first then Q2 then Q3

    // ---- Queue 1 (quantum = 4) ----
    for(int i=0;i<n;i++)
    {
        if(rem[i]<=0) continue;
        if(queue[i]!=1) continue;

        int run_time;
        if(rem[i]>q1) run_time=q1;
        else run_time=rem[i];

        // record timeline
        if(tl_count>0 && timeline_proc[tl_count-1]==proc[i])
            timeline_time[tl_count-1]+=run_time;
        else{
            timeline_proc[tl_count]=proc[i];
            timeline_time[tl_count]=run_time;
            tl_count++;
        }

        t+=run_time;
        rem[i]-=run_time;

        if(rem[i]==0){
            completed++;
            wt[i]=t-bt[i];
            if(wt[i]<0) wt[i]=0;
        }else{
            // move to queue 2
            queue[i]=2;
        }
    }

    // ---- Queue 2 (quantum = 8) ----
    for(int i=0;i<n;i++)
    {
        if(rem[i]<=0) continue;
        if(queue[i]!=2) continue;

        int run_time;
        if(rem[i]>q2) run_time=q2;
        else run_time=rem[i];

        if(tl_count>0 && timeline_proc[tl_count-1]==proc[i])
            timeline_time[tl_count-1]+=run_time;
        else{
            timeline_proc[tl_count]=proc[i];
            timeline_time[tl_count]=run_time;
            tl_count++;
        }

        t+=run_time;
        rem[i]-=run_time;

        if(rem[i]==0){
            completed++;
            wt[i]=t-bt[i];
            if(wt[i]<0) wt[i]=0;
        }else{
            queue[i]=3;
        }
    }

    // ---- Queue 3 (FCFS - run till done) ----
    for(int i=0;i<n;i++)
    {
        if(rem[i]<=0) continue;
        if(queue[i]!=3) continue;

        int run_time=rem[i];

        if(tl_count>0 && timeline_proc[tl_count-1]==proc[i])
            timeline_time[tl_count-1]+=run_time;
        else{
            timeline_proc[tl_count]=proc[i];
            timeline_time[tl_count]=run_time;
            tl_count++;
        }

        t+=run_time;
        rem[i]=0;
        completed++;
        wt[i]=t-bt[i];
        if(wt[i]<0) wt[i]=0;
    }

    for(int i=0;i<n;i++)
        tat[i]=wt[i]+bt[i];

    // show which queue each process ended in
    cout<<"\nQueue Info:"<<endl;
    cout<<"Q1 quantum = "<<q1<<endl;
    cout<<"Q2 quantum = "<<q2<<endl;
    cout<<"Q3 = FCFS (no quantum)"<<endl;

    float totalWt=0,totalTat=0;
    cout<<"\n";
    cout<<"P\tBT\tWT\tTAT"<<endl;
    cout<<"-----------------------------"<<endl;
    for(int i=0;i<n;i++){
        cout<<proc[i]<<"\t"<<bt[i]<<"\t"<<wt[i]<<"\t"<<tat[i]<<endl;
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
        int spaces=timeline_time[i];
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
        ctime+=timeline_time[i];
        for(int j=0;j<timeline_time[i]*2-1;j++) cout<<" ";
        if(ctime<10) cout<<" ";
        cout<<ctime;
    }
    cout<<endl;
}
