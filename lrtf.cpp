#include<iostream>
#include "header files/lrtf.h"
using namespace std;

// LRTF - Longest Remaining Time First (preemptive version of LJF)
// at every time unit pick the process with the longest remaining time
// opposite of SRTF basically

void lrtf(int proc[],int bt[],int n)
{
    int wt[100],tat[100],rem[100];
    int timeline_proc[500],timeline_time[500];
    int tl_count=0;

    for(int i=0;i<n;i++)
        rem[i]=bt[i];

    int completed=0,t=0;

    while(completed!=n)
    {
        // find process with longest remaining time
        int max_val=-1;
        int idx=-1;

        for(int i=0;i<n;i++){
            if(rem[i]>0 && rem[i]>max_val){
                max_val=rem[i];
                idx=i;
            }
        }

        if(idx==-1){
            t++;
            continue;
        }

        // record for timeline (merge if same process as last)
        if(tl_count>0 && timeline_proc[tl_count-1]==proc[idx]){
            timeline_time[tl_count-1]++;
        }else{
            timeline_proc[tl_count]=proc[idx];
            timeline_time[tl_count]=1;
            tl_count++;
        }

        rem[idx]--;
        t++;

        if(rem[idx]==0){
            completed++;
            wt[idx]=t-bt[idx];
            if(wt[idx]<0) wt[idx]=0;
        }
    }

    for(int i=0;i<n;i++)
        tat[i]=wt[i]+bt[i];

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
