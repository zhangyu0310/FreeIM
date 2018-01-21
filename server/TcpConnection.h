/*************************************************************************
	> File Name: TcpConnection.h
	> Author: 
	> Mail: 
	> Created Time: Sun 14 Jan 2018 01:33:27 PM CST
 ************************************************************************/

#ifndef _TCPCONNECTION_H
#define _TCPCONNECTION_H
#include "Buffer.h"

class TcpConnection
{
public:
    typedef void(*event_callback)(TcpConnection*);
    TcpConnection(int sockfd) : conn_fd(sockfd), close_cb(NULL) {}
    //~TcpConnection();
    int getConnfd() { return conn_fd; }
    void addCloseCallBack(event_callback cb) { close_cb = cb; }

    string getMessageAsString() { return _input.getMessageAsString(); }
    void setMessage(string message) { _output.setMessage(message); }

    void send();
    void send(string message)
    {
        this->setMessage(message);
        this->send();
    }
    int recv();
    void close();
private:
    int conn_fd;
    event_callback close_cb;
    Buffer _input;
    Buffer _output;
};
#endif
