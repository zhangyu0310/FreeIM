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
//#include <iostream>
#include <map>
#include <vector>
#include "ThreadLoop.h"
#include "UserInterface.h"
//using std::cout;
//using std::cin;
//using std::endl;
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
    typedef void(*event_callback)(evutil_socket_t, short, void*);
    typedef void(*ser_cb)(UserInterface*);
public:
    TcpServer(int port, int threads) : _port(port), thread_num(threads), _sockfd(0),
                                    _base(NULL), read_cb(NULL), write_cb(NULL)
    {
        self_pair = new int[thread_num];
        threads_pair = new int[thread_num];
    }
    //~TcpServer();
    void addReadCallBack(ser_cb cb) { read_cb = cb; }
    void addWriteCallBack(ser_cb cb) { write_cb = cb; }
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
    ser_cb read_cb;
    ser_cb write_cb;
    int *self_pair;
    int *threads_pair;
    map<int, int> load_map;
    vector<ThreadLoop*> _threads;

    //static void change_map(evutil_socket_t fd, short event, void *arg);
    //static void accept_cb(evutil_socket_t fd, short event, void *arg);
};
#endif
