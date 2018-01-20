/*************************************************************************
	> File Name: change.cpp
	> Author: 
	> Mail: 
	> Created Time: Sat 20 Jan 2018 12:50:32 AM CST
 ************************************************************************/

#include <iostream>
#include <string>
using namespace std;
#include "TcpServer.h"
#include "TcpConnection.h"
#include "ThreadLoop.h"
#include "UserInterface.h"
#include <json/json.h>

void read_cb(UserInterface *interface)
{
    //cout << "read_cb" << endl;
    TcpConnection *conn = interface->getConnection();
    if(interface->recv() <= 0)
    {
        interface->close();
        return;
    }
    string user_name = conn->getValueAsString("name");
    Json::Value val;
    val["message"] = "Hello";
    interface->writeEvent(val);
    //cout << "read_cb end" << endl;
    //TcpConnection *conn = interface->getConnection();
}
void write_cb(UserInterface *interface)
{
    //cout << "write_cb" << endl;
    interface->send();
}

int main()
{
    TcpServer server(1219, 2);
    server.addReadCallBack(read_cb);
    server.addWriteCallBack(write_cb);
    server.serverInit();
    server.run();
}
