/*************************************************************************
	> File Name: echo.cpp
	> Author: 
	> Mail: 
	> Created Time: Wed 24 Jan 2018 01:50:16 PM CST
 ************************************************************************/

#include <iostream>
#include <string>
#include <unistd.h>
#include <stdlib.h>
#include "TcpClient.h"
#include "TcpConnection.h"
using namespace std;

void connect_cb(TcpConnection *conn)
{
    conn->send("Hello!");
}

void message_cb(TcpConnection *conn)
{
    string mes = conn->getMessageAsString();
    cout << mes << endl;
    sleep(1);
    conn->send(mes);
}

void close_cb(TcpConnection *conn)
{
    cout << "Server is closed!" << endl;
    cout << "Bye!" << endl;
    exit(0);
}

int main()
{
    TcpClient echo(1219, "120.24.89.156");
    echo.addConnectCallBack(connect_cb);
    echo.addMessageCallBack(message_cb);
    echo.addCloseCallBack(close_cb);
    echo.clientInit();
    echo.run();
}
