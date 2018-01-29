/*************************************************************************
	> File Name: TcpClient.h
	> Author: 
	> Mail: 
	> Created Time: Wed 10 Jan 2018 08:35:52 PM CST
 ************************************************************************/

#ifndef _TCPCLIENT_H
#define _TCPCLIENT_H
#include <event.h>
#include <string.h>
#include "TcpConnection.h"
class TcpClient
{
public:
    typedef void(*event_callback)(TcpConnection*);
    TcpClient(const int port, const char *ip) : _port(port), _base(NULL), connect_cb(NULL),
                                        message_cb(NULL), close_cb(NULL), _sockfd(-1), connection(NULL)
    {
        strcpy(_ip, ip);
    }
    ~TcpClient()
    {
        //函数是瞎写的，查清楚再改
        //if(_base != NULL) event_delete_base(_base);
    }

    void addConnectCallBack(const event_callback cb) 
    { connect_cb = cb; }

    void addMessageCallBack(const event_callback cb)
    { message_cb = cb; }

    void addCloseCallBack(const event_callback cb)
    { close_cb = cb; }

    struct event_base* getBase() { return _base; }
    event_callback getMessageCallBack() { return message_cb; }
    event_callback getCloseCallBack() { return close_cb; }
    TcpConnection* getConnection() { return connection; }

    int clientInit();
    void run();
private:
    struct event_base *_base;
    event_callback connect_cb;
    event_callback message_cb;
    event_callback close_cb;
    int _port;
    int _sockfd;
    char _ip[32];
    TcpConnection *connection;
};
#endif
