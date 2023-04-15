//
//  SRTN.hpp
//  Project-02
//
//  Created by MBA on 4/13/23.
//

#ifndef SRTN_hpp
#define SRTN_hpp

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <string>
using namespace std;

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

void SRTN_Schedule(int NoProcess,vector<char>&CPU_Gantt,vector<char>&R_Gantt,SRTN a[4]);
void readProcess(int &n,SRTN a[4]);
void SRTN_Algo();

#endif /* SRTN_hpp */
