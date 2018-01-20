/*************************************************************************
	> File Name: TcpConnection.cpp
	> Author: 
	> Mail: 
	> Created Time: Wed 17 Jan 2018 09:07:21 PM CST
 ************************************************************************/

#include "TcpConnection.h"
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
using Json::Reader;

string TcpConnection::getValueAsString(string key)
{
    if(_val[key].isString())
    {
        return _val[key].asString();    
    }
    else
    {
        return string("");
    }
}

int TcpConnection::getValueAsInt(string key)
{
    if(_val[key].isInt())
    {
        return _val[key].asInt();
    }
    else
    {
        return -1;
    }
}

void TcpConnection::send()
{
    ::send(conn_fd, _val.toStyledString().c_str(), strlen(_val.toStyledString().c_str()), 0);
}

void TcpConnection::send(Value &buf)
{
    _val = buf;
    this->send();
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
    //len = ::recv(conn_fd, tmp, SIZE, 0);
    if(len <= 0) return len;
    Reader read;
    read.parse(buf, _val);
    return 1;
}

void TcpConnection::close()
{
    ::close(conn_fd);
}
