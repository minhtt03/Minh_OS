//
//  FCFS.hpp
//  Project-02
//
//  Created by MBA on 4/11/23.
//

#ifndef FCFS_hpp
#define FCFS_hpp

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <string>
using namespace std;

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
void FCFS_Schedule(int NoProcess,vector<char>&CPU_Gantt,vector<char>&R_Gantt,FCFS a[4]);
void readProcess(int &n, FCFS a[4]);
void FCFS_Algo();



#endif /* FCFS_hpp */
