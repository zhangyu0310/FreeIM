/*************************************************************************
	> File Name: TcpServer.h
	> Author: 
	> Mail: 
	> Created Time: Tue 09 Jan 2018 01:46:23 AM CST
 ************************************************************************/

#ifndef _TCPSERVER_H
#define _TCPSERVER_H
#include <event.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include <map>
#include <vector>
#include "ThreadLoop.h"
#include "TcpConnection.h"

using std::map;
using std::vector;

#define NOTHING         0
#define OK              1
#define SERVER_EXIST    3
#define CBFUNC_ERROR    4
#define FD_ERROR        5
#define BIND_ERROR      6
#define LISTEN_ERROR    7
#define EVENT_NEW_ERROR 8


class TcpServer
{
public:
    typedef void(*event_callback)(TcpConnection*);
    typedef void(*threads_init_callback)(ThreadLoop*);
public:
    TcpServer(const int port, const int threads) : _port(port), thread_num(threads), _sockfd(0),
                                    _base(NULL), threads_cb(NULL), accept_cb(NULL), message_cb(NULL), close_cb(NULL)
    {
        self_pair = new int[thread_num];
        threads_pair = new int[thread_num];
    }
    ~TcpServer()
    {
        delete[] self_pair;
        delete[] threads_pair;
    }
    void addThreadInitCallBack(const threads_init_callback cb) { threads_cb = cb; }
    void addAcceptCallBack(const event_callback cb) { accept_cb = cb; }
    void addMessageCallBack(const event_callback cb) { message_cb = cb; }
    void addCloseCallBack(const event_callback cb) { close_cb = cb; }
    //event_callback getAcceptCallBack() { return accept_cb; }
    struct event_base* getBase() { return _base; }
    map<int, int>* getMap() { return &load_map; }
    int serverInit();
    void run();
    //void stop();
private:
    int _port;
    int thread_num;
    int _sockfd;
    struct event_base *_base;
    threads_init_callback threads_cb;
    event_callback accept_cb;
    event_callback message_cb;
    event_callback close_cb;
    int *self_pair;
    int *threads_pair;
    map<int, int> load_map;
    vector<ThreadLoop*> _threads;
};
#endif
