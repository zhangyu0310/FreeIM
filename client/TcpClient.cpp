/*************************************************************************
	> File Name: TcpClient.cpp
	> Author: 
	> Mail: 
	> Created Time: Wed 10 Jan 2018 08:36:13 PM CST
 ************************************************************************/

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string>
#include <string.h>
#include "TcpClient.h"
#include "TcpConnection.h"
using std::string;

static void message_func(int fd, short event, void *arg)
{
    TcpClient *thiz = (TcpClient*)arg;
    TcpClient::event_callback message_cb = thiz->getMessageCallBack();
    struct event_base *base = thiz->getBase();
    TcpConnection *conn = thiz->getConnection();
    if(conn->recv() <= 0)
    {
        conn->close();
        delete conn;
    }
    else
    {
        message_cb(conn);
        if(conn->isClosed())
        {
            delete conn;
        }
        else
        {
            struct event *event_again = event_new(base, fd, event, message_func, arg);
            event_add(event_again, NULL);
        }
    }
}

int TcpClient::clientInit()
{
    if(_base != NULL) return 0;
    
    _base = event_base_new();
    if(_base == NULL) return -1;

    _sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(_sockfd == -1) return -1;

    struct sockaddr_in saddr;
    bzero(&saddr, sizeof(saddr));
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(_port);
    inet_pton(AF_INET, _ip, &saddr.sin_addr);

    int ret = connect(_sockfd, (struct sockaddr*)&saddr, sizeof(saddr));
    if(ret == -1) return -1;

    connection = new TcpConnection(_sockfd, close_cb);
    connect_cb(connection);

    struct event *conn_event = event_new(_base, _sockfd, EV_READ|EV_PERSIST, message_func, this);
    if(conn_event == NULL) return -1;
    event_add(conn_event, NULL);
    return 0;
}

void TcpClient::run()
{
    event_base_dispatch(_base);
}
