/*************************************************************************
	> File Name: shutdown.cpp
	> Author: 
	> Mail: 
	> Created Time: Mon 22 Jan 2018 02:02:39 AM CST
 ************************************************************************/

#include <iostream>
#include <string>
#include <map>
#include "TcpServer.h"
#include "TcpConnection.h"
using namespace std;

map<int, int> fd_count_map;

void accept_func(TcpConnection *conn)
{
    int fd = conn->getConnfd();
    fd_count_map[fd] = 0;
    cout << "FD: " << fd << " online" <<endl;
}
void message_func(TcpConnection *conn)
{
    int fd = conn->getConnfd();
    int count = fd_count_map[fd];
    if(count >= 10)
    {
        string mes = "shutdown";
        conn->send(mes);
        cout << "FD: " << fd << " shutdown" << endl;
        fd_count_map.erase(fd);
        conn->close();
    }
    else
    {
        string mes = "not shutdown";
        conn->send(mes);
        cout << "FD: " << fd << " not shutdown" << endl;
        ++fd_count_map[fd];
    }
}
void close_func(TcpConnection *conn)
{
    int fd = conn->getConnfd();
    fd_count_map.erase(fd);
    cout << "FD: " << fd << " closed" << endl;
}

int main()
{
    TcpServer server(1219, 3);
    server.addAcceptCallBack(accept_func);
    server.addMessageCallBack(message_func);
    server.addCloseCallBack(close_func);
    server.serverInit();
    server.run();
}
