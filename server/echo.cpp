/*************************************************************************
	> File Name: echo.cpp
	> Author: 
	> Mail: 
	> Created Time: Wed 17 Jan 2018 01:45:13 AM CST
 ************************************************************************/

#include <iostream>
#include "TcpServer.h"
#include <pthread.h>
using namespace std;

void read_func(UserInterface *interface)
{
    int fd = interface->getFileDescriptor();
    char tmp[16] = {0};
    int ret = recv(fd, tmp, 16, 0);
    if(ret <= 0)
    {
        interface->close();
        return;
    }
    interface->writeEvent();
    cout << "ThreadID: " << pthread_self() << endl;
    //send(fd, tmp, ret, 0);
}

void write_func(UserInterface *interface)
{
    int fd = interface->getFileDescriptor();
    send(fd, "Server Hello", 13, 0);
    return;
}

int main()
{
    TcpServer echo(1219, 3);
    echo.addReadCallBack(read_func);
    echo.addWriteCallBack(write_func);
    echo.serverInit();
    //cout << "Init is over" << endl;
    echo.run();
}
