/*************************************************************************
	> File Name: echo.cpp
	> Author: 
	> Mail: 
	> Created Time: Wed 17 Jan 2018 01:45:13 AM CST
 ************************************************************************/

#include <iostream>
#include "TcpServer.h"
#include "TcpConnection.h"
#include "Buffer.h"
#include <string>
using namespace std;

void accept_func(TcpConnection *conn)
{
    int fd = conn->getConnfd();
    cout << "FD: " << fd << " is online" << endl;
}

void message_func(TcpConnection *conn)
{
    string mess = conn->getMessageAsString();
    cout << "ThreadID: " << pthread_self() << endl;
    conn->send(mess);
}

void close_func(TcpConnection *conn)
{
    cout << "FD: " << conn->getConnfd() << " is closed" << endl;
}

int main()
{
    TcpServer echo(1219, 3);
    echo.addAcceptCallBack(accept_func);
    echo.addMessageCallBack(message_func);
    echo.addCloseCallBack(close_func);
    echo.serverInit();
    echo.run();
}
