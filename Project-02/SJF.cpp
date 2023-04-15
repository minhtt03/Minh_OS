//
//  SJF.cpp
//  Project-02
//
//  Created by MBA on 4/13/23.
//

#include "SJF.hpp"
void readProcess(int &n,SJF a[4])
{
    ifstream fin;
    fin>>n;
    fin.ignore();
    for ( int i=0; i<n; i++ )
    {
        string process ="";
        string temp ="";
        int flag =-1;
        
        getline(fin,process);
        char arrival[process.length() +1];
        char cpu[process.length() +1];
        char r[process.length() +1];
        for ( int j=0; j<process.size();j++)
        {
            
            if ( process[j] != ' ')
            {
                if ( flag == 1)//arrival time
                {
                    strcpy(arrival, process.c_str());
                    a[i].ArrivalTime =atoi(arrival);
                    flag=0;
                }
                else if ( flag ==0 )//cpu
                {
                    stpcpy(cpu, process.c_str());
                    a[i].CPU_Burst.push_back(atoi(cpu));
                    flag = 1;
                }
                else //r
                {
                    stpcpy(r, process.c_str());
                    a[i].CPU_Burst.push_back(atoi(r));
                    flag = 0;
                }
            }
            else
            {
                memset(arrival, '\0', sizeof(arrival));
                memset(cpu, '\0', sizeof(cpu));
                memset(r, '\0', sizeof(r));
            }
        }
    }
}

void SJF_Schedule(int NoProcess, vector<char>&CPU_Gantt, vector<char> &R_Gantt,SJF a[4])
{
    vector<int> Ready_CPU;//index of process in CPU queue
    vector<int> Ready_R;//index of process in R queue
    int Time_CPUAcess =0;
    int Time = 0;
    int FinishedProcess = 0;
    
    while(true)
    {
        for ( int i=0; i<NoProcess; i++)
        {
            if (a[i].hasArrived != false && a[i].ArrivalTime == Time)
            {
                Ready_CPU.push_back(i);
                a[i].hasArrived = true;
            }
        }
        
        int c;//Order in Ready_CPU
        int r;//Order in Ready_R
        if ( Ready_CPU.size() != 0)//check at time 0 with out any process
        {
            c=Ready_CPU[0];
        if (a[c].CPU_Burst[0]==0 && Ready_CPU.size() != 0)
        {
            a[c].CPU_Burst.erase(a[c].CPU_Burst.begin());
            Ready_CPU.erase(Ready_CPU.begin());//push Process
            if ( a[c].R_Burst.size() != 0)//check if have R
                Ready_R.push_back(c);
            else//Finished process
            {
                a[c].CompleteTime=Time;
                FinishedProcess++;
            }
        }
        }
        if (Ready_R.size() !=0 )
        {
            r=Ready_R[0];
        if (a[r].R_Burst[0]==0 && Ready_R.size() != 0)
        {
            a[r].R_Burst.erase(a[r].R_Burst.begin());
            Ready_R.erase(Ready_R.begin());
            if (a[r].CPU_Burst.size() != 0)//check if there are any CPU burst
            {
                Ready_CPU.push_back(r);
                a[r].hasArrived=true;

            }//Finished process
            else
            {
                a[r].CompleteTime=Time;
                FinishedProcess++;
            }
        }
        }

        if (FinishedProcess==NoProcess)break;
        
        if ( Time_CPUAcess ==0)
        {
            for ( int i =0; i < Ready_CPU.size();i++)
            {
                if ( a[Ready_CPU[i]].CPU_Burst[0] < a[Ready_CPU[0]].CPU_Burst[0])
                    swap(Ready_CPU[0],Ready_CPU[i]);
            }
        }
        //Gantt Chart CPU
        if ( Ready_CPU.size() != 0)
        {
            c = Ready_CPU[0];
            if ( a[c].hasArrived == true)
            {
                Time_CPUAcess = a[c].CPU_Burst[0];
                a[c].hasArrived=false;
            }
            Time_CPUAcess--;
            CPU_Gantt.push_back(char(c+1)+48);
            a[c].CPU_Burst[0]--;//decrease burst time
        }
        else
            CPU_Gantt.push_back('_');
        //Gantt Chart R
        if ( Ready_R.size() != 0)
        {
            r=Ready_R[0];
            R_Gantt.push_back(char(r + 1)+ 48);
            a[r].R_Burst[0]--;
        }
        else
            R_Gantt.push_back('_');
        Time++;
    }
    return;
}
void SJF_Algo()
{
    ofstream fout;
    int n;
    SJF a[4];
    readProcess(n, a);
    vector<char>cpu;
    vector<char>r;
    SJF_Schedule(n, cpu, r, a);
    for ( int i=0;i<cpu.size();i++)
    fout<<cpu[i]<<" ";
    fout<<endl;
    for ( int i=0;i<r.size();i++)
    fout<<r[i]<<" ";
    fout<<endl;
    for ( int i=0;i<n;i++)
    fout<<a[i].CompleteTime-a[i].ArrivalTime<<" ";
}
