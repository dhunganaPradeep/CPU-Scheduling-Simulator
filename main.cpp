#include<iostream>
#include "header files/fcfs.h"
#include "header files/roundrobin.h"
#include "header files/priority.h"
#include "header files/sjf.h"
#include "header files/srtf.h"
#include "header files/hrrn.h"
#include "header files/ljf.h"
#include "header files/lrtf.h"
#include "header files/mlfq.h"

using namespace std;

int main()
{
    int choice;
    char again;

    cout<<"========================================="<<endl;
    cout<<"      CPU Scheduling Simulator"<<endl;
    cout<<"========================================="<<endl;

    do
    {
        cout<<"\n--- Menu ---"<<endl;
        cout<<"1. FCFS (First Come First Serve)"<<endl;
        cout<<"2. Round Robin"<<endl;
        cout<<"3. Priority Scheduling"<<endl;
        cout<<"4. SJF (Shortest Job First)"<<endl;
        cout<<"5. SRTF (Shortest Remaining Time First)"<<endl;
        cout<<"6. HRRN (Highest Response Ratio Next)"<<endl;
        cout<<"7. LJF (Longest Job First)"<<endl;
        cout<<"8. LRTF (Longest Remaining Time First)"<<endl;
        cout<<"9. MLFQ (Multi Level Feedback Queue)"<<endl;
        cout<<"10. Exit"<<endl;
        cout<<"\nEnter choice: ";
        cin>>choice;

        if(choice==10){
            cout<<"\nBye!\n";
            break;
        }

        if(choice<1 || choice>10){
            cout<<"Invalid choice try again"<<endl;
            continue;
        }

        int n;
        cout<<"\nHow many processes? ";
        cin>>n;

        if(n<=0 || n>100){
            cout<<"bruh enter a valid number (1-100)"<<endl;
            continue;
        }

        int proc[100], bt[100];

        // assign process ids 1,2,3...
        for(int i=0;i<n;i++)
            proc[i] = i+1;

        cout<<"Enter burst times: ";
        for(int i=0;i<n;i++)
            cin>>bt[i];

        if(choice==1)
        {
            cout<<"\n>> FCFS Scheduling <<"<<endl;
            fcfs(proc,bt,n);
        }
        else if(choice==2)
        {
            int q;
            cout<<"Enter time quantum: ";
            cin>>q;
            if(q<=0){
                cout<<"quantum has to be positive bro"<<endl;
                continue;
            }
            cout<<"\n>> Round Robin Scheduling (q="<<q<<") <<"<<endl;
            roundRobin(proc,bt,n,q);
        }
        else if(choice==3)
        {
            int prio[100];
            cout<<"Enter priorities (lower = higher priority): ";
            for(int i=0;i<n;i++)
                cin>>prio[i];

            cout<<"\n>> Priority Scheduling <<"<<endl;
            prioritySched(proc,bt,prio,n);
        }
        else if(choice==4)
        {
            cout<<"\n>> SJF Scheduling <<"<<endl;
            sjf(proc,bt,n);
        }
        else if(choice==5)
        {
            cout<<"\n>> SRTF Scheduling <<"<<endl;
            srtf(proc,bt,n);
        }
        else if(choice==6)
        {
            cout<<"\n>> HRRN Scheduling <<"<<endl;
            hrrn(proc,bt,n);
        }
        else if(choice==7)
        {
            cout<<"\n>> LJF Scheduling <<"<<endl;
            ljf(proc,bt,n);
        }
        else if(choice==8)
        {
            cout<<"\n>> LRTF Scheduling <<"<<endl;
            lrtf(proc,bt,n);
        }
        else if(choice==9)
        {
            cout<<"\n>> MLFQ Scheduling <<"<<endl;
            mlfq(proc,bt,n);
        }

        cout<<"\nDo you want to continue? (y/n): ";
        cin>>again;

    } while(again=='y' || again=='Y');

    if(again!='y' && again!='Y' && choice!=10)
        cout<<"\nThanks for using the scheduler!\n";

    return 0;
}
