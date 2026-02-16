#include <iostream>
#include "header files/srtf.h"
using namespace std;

// SRTF (Shortest Remaining Time First)
// This is the preemptive version of SJF
// At every time step, we check if there's a process with even shorter time
// Note: Since all processes currently arrive at time 0, it will look like SJF
// but the logic here supports preemption if we add arrival times later

void srtf(int proc[], int bt[], int n) {
    int wt[100], tat[100], rem[100];
    int timeline_proc[500], timeline_time[500];
    int tl_count = 0;

    for(int i=0; i<n; i++) {
        rem[i] = bt[i];
    }

    int completed = 0, t = 0, min_idx = -1;
    int min_val = 999999;
    bool found = false;

    // We run until everyone is done
    while(completed != n) {
        min_val = 999999;
        found = false;

        // Find process with shortest remaining time
        for(int i=0; i<n; i++) {
            if(rem[i] > 0 && rem[i] < min_val) {
                min_val = rem[i];
                min_idx = i;
                found = true;
            }
        }

        if(!found) {
            t++;
            continue;
        }

        // Record for timeline
        if(tl_count > 0 && timeline_proc[tl_count-1] == proc[min_idx]) {
            timeline_time[tl_count-1]++;
        } else {
            timeline_proc[tl_count] = proc[min_idx];
            timeline_time[tl_count] = 1;
            tl_count++;
        }

        // Run for 1 unit of time
        rem[min_idx]--;
        t++;

        if(rem[min_idx] == 0) {
            completed++;
            // waiting time = total time - burst time
            wt[min_idx] = t - bt[min_idx];
            if(wt[min_idx] < 0) wt[min_idx] = 0;
        }
    }

    for(int i=0; i<n; i++) {
        tat[i] = wt[i] + bt[i];
    }

    float totalWt=0, totalTat=0;
    cout << "\n";
    cout << "P\tBT\tWT\tTAT" << endl;
    cout << "-----------------------------" << endl;
    for(int i=0; i<n; i++) {
        cout << proc[i] << "\t" << bt[i] << "\t" << wt[i] << "\t" << tat[i] << endl;
        totalWt += wt[i];
        totalTat += tat[i];
    }

    cout << "\nAvg WT  = " << totalWt/n << endl;
    cout << "Avg TAT = " << totalTat/n << endl;

    cout << "\nTimeline:\n";
    cout << " ";
    for(int i=0; i<tl_count; i++) {
        for(int j=0; j<timeline_time[i]; j++) cout << "--";
        cout << " ";
    }
    cout << endl;

    cout << "|";
    for(int i=0; i<tl_count; i++) {
        int spaces = timeline_time[i];
        for(int j=0; j<spaces-1; j++) cout << " ";
        cout << "P" << timeline_proc[i];
        for(int j=0; j<spaces-1; j++) cout << " ";
        cout << "|";
    }
    cout << endl;

    cout << " ";
    for(int i=0; i<tl_count; i++) {
        for(int j=0; j<timeline_time[i]; j++) cout << "--";
        cout << " ";
    }
    cout << endl;

    cout << "0";
    int ctime=0;
    for(int i=0; i<tl_count; i++) {
        ctime += timeline_time[i];
        for(int j=0; j<timeline_time[i]*2-1; j++) cout << " ";
        if(ctime<10) cout << " ";
        cout << ctime;
    }
    cout << endl;
}
