//
//  RR.hpp
//  Project-02
//
//  Created by MBA on 4/13/23.
//

#ifndef RR_hpp
#define RR_hpp

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <string>
#include <string.h>
using namespace std;

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
void RR_Schedule(int NoProcess,int Quantum,vector<char>&CPU_Gantt,vector<char>&R_Gantt,RR a[4]);
void readProcess(int &NoProcess,int &Quantum, RR a[4]);
void RR_Algo();

#endif /* RR_hpp */
