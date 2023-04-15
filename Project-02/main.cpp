//
//  main.cpp
//  Project-02
//
//  Created by MBA on 4/11/23.
//

#include <iostream>
#include <fstream>
#include "FCFS.hpp"
#include "SJF.hpp"
#include "RR.hpp"
#include "SRTN.hpp"
using namespace std;

int main(int argc, const char * argv[])
{
    fstream f;
    f.open(argv[1],ios::in);
    f.open(argv[2],ios::out);
    int Type;
    f>>Type;
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
    f.close();
    return 0;
}
