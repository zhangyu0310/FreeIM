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
#include <map>

map<string, int> user_fd_map;

void accept_cb(UserInterface *interface)
{
    TcpConnection *conn = interface->getConnection();
    int cli_fd = interface->getFileDescriptor();
    conn->recv();
    string user_name = conn->getValueAsString("username");
    user_fd_map[user_name] = cli_fd;
}
void read_cb(UserInterface *interface)
{
    //cout << "read_cb" << endl;
    TcpConnection *conn = interface->getConnection();
    if(conn->recv() <= 0)
    {
        interface->close();
        return;
    }
    string to_name = conn->getValueAsString("Toname");
    string my_name = conn->getValueAsString("Myname");
    string mess = conn->getValueAsString("mess");
    Json::Value val;
    val["Toname"] = my_name;
    val["Myname"] = to_name;
    val["message"] = mess;
    interface->writeEvent(val);
    //cout << "read_cb end" << endl;
    //TcpConnection *conn = interface->getConnection();
}
void write_cb(UserInterface *interface)
{
    //cout << "write_cb" << endl;
    TcpConnection *conn = interface->getConnection();
    string my_name = conn->getValueAsString("Myname");
    map<string, int>::iterator it = user_fd_map.find(my_name);
    TcpConnection connect(it->second);
    connect.send(conn->getValue());
}

int main()
{
    TcpServer server(1219, 2);
    server.addAcceptCallBack(accept_cb);
    server.addReadCallBack(read_cb);
    server.addWriteCallBack(write_cb);
    server.serverInit();
    server.run();
}
