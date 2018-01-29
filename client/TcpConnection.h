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
    TcpConnection(const int sockfd) : _closed(false), conn_fd(sockfd), close_cb(NULL) {}
    TcpConnection(const int sockfd, const event_callback cb) : _closed(false), conn_fd(sockfd), close_cb(cb) {}
    //~TcpConnection();
    int getConnfd() { return conn_fd; }
    void addCloseCallBack(event_callback cb) { close_cb = cb; }

    string getMessageAsString() { return _input.getMessageAsString(); }
    void setMessage(const string &message) { _output.setMessage(message); }

    void send();
    void send(const string &message)
    {
        this->setMessage(message);
        this->send();
    }
    int recv();
    void close();

    bool isClosed() { return _closed == 1; }
private:
    bool _closed;
    int conn_fd;
    event_callback close_cb;
    Buffer _input;
    Buffer _output;
};
#endif
