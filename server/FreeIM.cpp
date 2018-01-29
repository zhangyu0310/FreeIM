/*************************************************************************
	> File Name: FreeIM.cpp
	> Author: 
	> Mail: 
	> Created Time: Wed 24 Jan 2018 08:56:10 PM CST
 ************************************************************************/

#include <map>
#include <pthread.h>
#include "FreeIM_Server.h"
#include "DataBase.h"
using namespace std;
#define THREADS_NUM 3

int main()
{
    FreeIM IM(1219, THREADS_NUM);
    IM.init();
    IM.run();
}
