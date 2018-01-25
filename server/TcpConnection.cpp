/*************************************************************************
	> File Name: TcpConnection.cpp
	> Author: 
	> Mail: 
	> Created Time: Wed 17 Jan 2018 09:07:21 PM CST
 ************************************************************************/

#include "TcpConnection.h"
#include "ThreadLoop.h"
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string>
using std::string;

void TcpConnection::send()
{
    ::send(conn_fd, _output.getMessageAsCstr(), _output.size(), 0);
}

int TcpConnection::recv()
{
    const int SIZE = 128;
    char tmp[SIZE] = {0};
    string buf;
    int len = 0;
    while((len = ::recv(conn_fd, tmp, SIZE, 0)) > 0)
    {
        buf += tmp;
        bzero(&tmp, len);
        if(len < SIZE) break;
    }
    if(len <= 0) return len;
    _input.setMessage(buf);
    return 1;
}

void TcpConnection::close()
{
    if(_closed == true) return;
    _closed = true;
    if(_loop == NULL) return;

    if(close_cb != NULL)
    {
        close_cb(this);
    }
    _loop->delConntion(conn_fd);
    _loop->loadMinus();
    ::close(conn_fd);
}
