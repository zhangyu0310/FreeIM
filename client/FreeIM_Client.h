/*************************************************************************
	> File Name: FreeIM_Client.h
	> Author: 
	> Mail: 
	> Created Time: Wed 24 Jan 2018 05:43:29 PM CST
 ************************************************************************/

#ifndef _FREEIM_CLIENT_H
#define _FREEIM_CLIENT_H
#include "TcpConnection.h"
#include "TcpClient.h"

enum
{
    MSG_TYPE_REGISTER = 0,
    MSG_TYPE_LOGIN    = 1,
    MSG_TYPE_P2PMES   = 2,
    MSG_TYPE_GROUP    = 3,
    MSG_TYPE_LIST     = 4,
    MSG_TYPE_CLOSE    = 5
};

void connect_cb(TcpConnection*);
void message_cb(TcpConnection*);
void close_cb(TcpConnection*);

class FreeIM
{
public:
    FreeIM(const int port, const char *ip) : _client(port, ip)
    {
        _client.addConnectCallBack(connect_cb);
        _client.addMessageCallBack(message_cb);
        _client.addCloseCallBack(close_cb);
    }

    int clientInit()
    {
        return _client.clientInit();
    }

    void run()
    {
        _client.run();
    }
private:
    TcpClient _client;
};
#endif
