//
//  main.cpp
//  Project-02
//
//  Created by MBA on 4/11/23.
//

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <string>

using namespace std;
ifstream fin;
ofstream fout;

/* FCFS */
class FCFS
{
public:
    int num;
    int ArrivalTime;
    int WaitTime = 0;
    int TurnAroundTime = 0 ;
    int CompleteTime;
    bool hasArrived = false;
    
    vector<int>CPU_Burst;
    vector<int>R_Burst;
};

void readProcess(int &n,FCFS a[4])
{
    fin>> n; //Number of processes

    fin.ignore();
    for (int i = 0; i < n; i++)
    {
        // char* s[14]; 
        // memset(s, 0, 13); // Clear the array
        string s = "";
        string temp = "";
        int y = 1;

        getline(fin, s);
        if (s[s.size() - 1] != ' ') s += " ";
        int flip_flop = -1; // 0: CPU Burst Time, 1: IO Burst Time
        for (int j = 0; j < s.size(); j++)
            if (a[i].CPU_Burst.size() == 3 && a[i].R_Burst.size() == 3) break;
            else{
                if (s[j] == ' ') // If s[j] is not a space
                {
                    if (flip_flop == -1)
                    {
                        int x = atoi(temp.c_str());
                        a[i].ArrivalTime = x;
                        flip_flop = 0;
                    }
                    else if (flip_flop == 0){
                        //Read CPU Burst Time
                        int x = atoi(temp.c_str());
                        a[i].CPU_Burst.push_back(x);
                        flip_flop = 1;
                    }
                    else {
                        //Read IO Burst Time
                        int x = atoi(temp.c_str());
                        a[i].R_Burst.push_back(x);
                        flip_flop = 0;
                    }
                    temp = "";
                }
                else temp += s[j];
            }
    }
}

void FCFS_Schedule(int NoProcess, vector<char>&CPU_Gantt, vector<char> &R_Gantt,FCFS a[4])
{
    vector<int> Ready_CPU;//index of process in CPU queue
    vector<int> Ready_R;//index of process in R queue

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
        {    c=Ready_CPU[0];
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
        {   r=Ready_R[0];
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
        //Gantt Chart CPU
        if ( Ready_CPU.size() != 0)
        {
            c = Ready_CPU[0];
            if ( a[c].hasArrived == true)
            {
                a[c].hasArrived=false;
            }
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

void FCFS_Algo()
{
    
    int n;
    FCFS a[4];
    readProcess(n, a);
    vector<char>cpu;
    vector<char>r;
    FCFS_Schedule(n, cpu, r, a);
    for ( int i=0;i<cpu.size();i++)
    fout<<cpu[i]<<" ";
    fout<<endl;
    for ( int i=0;i<r.size();i++)
    fout<<r[i]<<" ";
    fout<<endl;
    for ( int i=0;i<n;i++)
    fout<<a[i].CompleteTime-a[i].ArrivalTime<<" ";
    
}

/* RR */
class RR
{
public:
    int Num;
    int TimeLeft;
    int ArrivalTime;
    int WaitTime;
    int TurnAroundTime;
    int CompleteTime;
    bool hasArrived = false;
    
    vector<int>CPU_Burst;
    vector<int>R_Burst;
   
};

void readProcess(int &n,int &Quantum ,RR a[4])
{
    
    fin>>n;
    fin.ignore();
    fin>>Quantum;
    fin.ignore();
    for ( int i=0; i<n; i++ )
    {
        string process;
        string temp;
        int flag =-1;
        
        getline(fin,process);

        char arrival[process.size() +1];
        char cpu[process.size() +1];
        char r[process.size() +1];
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
                    strcpy(cpu, process.c_str());
                    a[i].CPU_Burst.push_back(atoi(cpu));
                    flag = 1;
                }
                else //r
                {
                    strcpy(r, process.c_str());
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

void RR_Schedule(int NoProcess,int Quantum, vector<char>&CPU_Gantt, vector<char> &R_Gantt,RR a[4])
{
    vector<int> Ready_CPU;//index of process in CPU queue
    vector<int> Ready_R;//index of process in R queue
    int Time_CPUAcess ;
    int Time_RAcess;
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
                a[i].TimeLeft=Quantum;
            }
        }
        
        int c;//Order in Ready_CPU
        int r;//Order in Ready_R
        if ( Ready_CPU.size() != 0)//check at time 0 with out any process
        {
            c=Ready_CPU[0];
            if ( a[c].TimeLeft==0)
            {
                if (a[c].CPU_Burst[0]==0  )
                {
                    if ( Ready_CPU.size() != 0)
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
                Ready_CPU.erase(Ready_CPU.begin());
                Ready_CPU.push_back(c);
                a[c].TimeLeft = Quantum;
                a[c].hasArrived = true;
                Time_CPUAcess = 0;
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
        //Gantt Chart CPU
        if ( Ready_CPU.size() != 0)
        {
            c = Ready_CPU[0];
            if ( a[c].hasArrived == true)
            {
                Time_CPUAcess = a[c].CPU_Burst[0];
                a[c].hasArrived=false;
            }
            Time_CPUAcess=a[c].CPU_Burst[0];
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
            Time_RAcess=a[r].R_Burst[0];
            R_Gantt.push_back(char(r + 1)+ 48);
            a[r].R_Burst[0]--;
        }
        else
            R_Gantt.push_back('_');
        Time++;
    }
    return;
}

void RR_Algo()
{
    
    int n;
    int Quantum;
    RR a[4];
    readProcess(n,Quantum, a);
    vector<char>cpu;
    vector<char>r;
    RR_Schedule(n,Quantum, cpu, r, a);
    for ( int i=0;i<cpu.size();i++)
    fout<<cpu[i]<<" ";
    fout<<endl;
    for ( int i=0;i<r.size();i++)
    fout<<r[i]<<" ";
    fout<<endl;
    for ( int i=0;i<n;i++)
    fout<<a[i].CompleteTime-a[i].ArrivalTime<<" ";
}

/* SJF */
class SJF
{
public:
    int Num;
    int ArrivalTime;
    int WaitTime;
    int TurnAroundTime;
    int CompleteTime;
    bool hasArrived = false;
    
    vector<int>CPU_Burst;
    vector<int>R_Burst;
    
};

void readProcess(int &n,SJF a[4])
{
    fin>> n; //Number of processes

    fin.ignore();
    for (int i = 0; i < n; i++)
    {
        // char* s[14]; 
        // memset(s, 0, 13); // Clear the array
        string s = "";
        string temp = "";
        int y = 1;

        getline(fin, s);
        if (s[s.size() - 1] != ' ') s += " ";
        int flip_flop = -1; // 0: CPU Burst Time, 1: IO Burst Time
        for (int j = 0; j < s.size(); j++)
            if (a[i].CPU_Burst.size() == 3 && a[i].R_Burst.size() == 3) break;
            else{
                if (s[j] == ' ') // If s[j] is not a space
                {
                    if (flip_flop == -1)
                    {
                        int x = atoi(temp.c_str());
                        a[i].ArrivalTime = x;
                        flip_flop = 0;
                    }
                    else if (flip_flop == 0){
                        //Read CPU Burst Time
                        int x = atoi(temp.c_str());
                        a[i].CPU_Burst.push_back(x);
                        flip_flop = 1;
                    }
                    else {
                        //Read IO Burst Time
                        int x = atoi(temp.c_str());
                        a[i].R_Burst.push_back(x);
                        flip_flop = 0;
                    }
                    temp = "";
                }
                else temp += s[j];
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

/* SRTN */
class SRTN
{
public:
    int num;
    int ArrivalTime;
    int WaitTime;
    int TurnAroundTime;
    int CompleteTime;
    bool hasArrived = false;
    
    vector<int>CPU_Burst;
    vector<int>R_Burst;
};

void read_Process(int &n,SRTN a[4])
{
    fin>> n; //Number of processes

    fin.ignore();
    for (int i = 0; i < n; i++)
    {
        // char* s[14]; 
        // memset(s, 0, 13); // Clear the array
        string s = "";
        string temp = "";
        int y = 1;

        getline(fin, s);
        if (s[s.size() - 1] != ' ') s += " ";
        int flip_flop = -1; // 0: CPU Burst Time, 1: IO Burst Time
        for (int j = 0; j < s.size(); j++)
            if (a[i].CPU_Burst.size() == 3 && a[i].R_Burst.size() == 3) break;
            else{
                if (s[j] == ' ') // If s[j] is not a space
                {
                    if (flip_flop == -1)
                    {
                        int x = atoi(temp.c_str());
                        a[i].ArrivalTime = x;
                        flip_flop = 0;
                    }
                    else if (flip_flop == 0){
                        //Read CPU Burst Time
                        int x = atoi(temp.c_str());
                        a[i].CPU_Burst.push_back(x);
                        flip_flop = 1;
                    }
                    else {
                        //Read IO Burst Time
                        int x = atoi(temp.c_str());
                        a[i].R_Burst.push_back(x);
                        flip_flop = 0;
                    }
                    temp = "";
                }
                else temp += s[j];
            }
    }
}

void SRTN_Schedule(int NoProcess,vector<char>CPU_Gantt,vector<char>R_Gantt,SRTN a[4])
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
                if ( a[i].CPU_Burst[0] == a[Ready_CPU[0]].CPU_Burst[0] )//if process cpu burst in queue = process cpu burst
                {
                    if (a[Ready_CPU[0]].hasArrived == false)//if process hasnt arrived
                    {
                        a[Ready_CPU[0]].hasArrived = true;
                    }
                    swap(Ready_CPU[0], Ready_CPU[Ready_CPU.size() - 1]); //swap
                    
                }
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
        if (Ready_CPU.size() != 0)
            for (int i = 0; i < (Ready_CPU.size() - 1); i++)
        {
                int temp = a[Ready_CPU[i]].CPU_Burst[0];//CPU burst of first index process

                for (int j = i + 1; j < Ready_CPU.size(); j++)
                {
                    if (temp > a[Ready_CPU[j]].CPU_Burst[0])
                    {
                        if (i == 0 && a[Ready_CPU[i]].hasArrived ==false)
                        {
                                a[i].hasArrived = true;
                        }
                        swap(Ready_CPU[j], Ready_CPU[i]);//swap index of process
                        temp = a[Ready_CPU[i]].CPU_Burst[0];
                    }
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

void SRTN_Algo()
{
    
    int n;
    SRTN a[4];
    read_Process(n, a);
    vector<char>cpu;
    vector<char>r;
    SRTN_Schedule(n, cpu, r, a);
    for ( int i=0;i<cpu.size();i++)
    fout<<cpu[i]<<" ";
    fout<<endl;
    for ( int i=0;i<r.size();i++)
    fout<<r[i]<<" ";
    fout<<endl;
    for ( int i=0;i<n;i++)
    fout<<a[i].CompleteTime-a[i].ArrivalTime<<" ";
}

// int main(int argc, const char * argv[])
int main()
{
    
    // fin.open(argv[1]);
    // fout.open(argv[2]);
    fin.open("Input.txt");
    fout.open("Output.txt");
    int Type;
    fin>>Type;
    switch(Type)
    {
        case 1:
            FCFS_Algo();
        case 2:
            RR_Algo();
        case 3:
            SJF_Algo();
        case 4:
            SRTN_Algo();
            break;
        default:break;
    }
    fin.close();
    fout.close();
    return 0;
}
