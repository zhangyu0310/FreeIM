/*************************************************************************
	> File Name: FreeIM.cpp
	> Author: 
	> Mail: 
	> Created Time: Wed 24 Jan 2018 08:56:10 PM CST
 ************************************************************************/

#include <iostream>
#include <string>
#include "FreeIM_Server.h"
#include "DataBase.h"
using namespace std;
DataBase db;

int main()
{
    FreeIM IM(1219, 3);
    IM.init();
    IM.run();
}
