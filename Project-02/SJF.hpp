//
//  SJF.hpp
//  Project-02
//
//  Created by MBA on 4/13/23.
//

#ifndef SJF_hpp
#define SJF_hpp

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <string>
using namespace std;

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
void SJF_Schedule(int NoProcess,vector<char>&CPU_Gantt,vector<char>&R_Gantt,SJF a[4]);
void readProcess(int &n, SJF a[4]);
void SJF_Algo();

#endif /* SJF_hpp */
