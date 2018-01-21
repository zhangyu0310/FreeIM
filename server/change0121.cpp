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
#include <map>

map<string, int> user_fd_map;

void accept_func(TcpConnection *conn)
{
    conn->recv();
    string user_name = conn->getMessageAsString();
    user_fd_map[user_name] = conn->getConnfd();
    cout << "FD: " << conn->getConnfd() << " is online" << endl;
}

void message_func(TcpConnection *conn)
{
    string message = conn->getMessageAsString();
    map<string, int>::iterator it = user_fd_map.begin();
    for(; it != user_fd_map.end(); ++it)
    {
        TcpConnection tmp_conn(it->second);
        tmp_conn.send(message);
    }
}

void close_func(TcpConnection *conn)
{
    int fd = conn->getConnfd();

    map<string, int>::iterator it = user_fd_map.begin();
    for(; it != user_fd_map.end(); ++it)
    {
        if(it->second == fd)
        {
            user_fd_map.erase(it);
            break;
        }
    }
    cout << "FD: " << fd << " is closed" << endl;
}

int main()
{
    TcpServer server(1219, 2);
    server.addAcceptCallBack(accept_func);
    server.addMessageCallBack(message_func);
    server.addCloseCallBack(close_func);
    server.serverInit();
    server.run();
}
