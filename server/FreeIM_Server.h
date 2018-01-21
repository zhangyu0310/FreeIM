/*************************************************************************
	> File Name: FreeIM_Server.h
	> Author: 
	> Mail: 
	> Created Time: Mon 22 Jan 2018 12:27:03 AM CST
 ************************************************************************/

#ifndef _FREEIM_SERVER_H
#define _FREEIM_SERVER_H
#include "TcpServer.h"
#include "TcpConnection.h"

enum
{
    MSG_TYPE_REGISTER = 0,
    MSG_TYPE_LOGIN    = 1,
    MSG_TYPE_P2PMES   = 2,
    MSG_TYPE_GROUP    = 3,
    MSG_TYPE_LIST     = 4,
    MSG_TYPE_CLOSE    = 5
};

class FreeIM
{
public:
    FreeIM(int port, int threads) : _server(port, threads)
    {
        _server.addAcceptCallBack(accept_func);
        _server.addMessageCallBack(message_func);
        _server.addCloseCallBack(close_func);
    }

    void init();
    void run();
private:
    static void accept_func(TcpConnection*);
    static void message_func(TcpConnection*);
    static void close_func(TcpConnection*);
    TcpServer _server;
};
#endif
