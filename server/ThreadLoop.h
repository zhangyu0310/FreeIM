/*************************************************************************
	> File Name: ThreadLoop.h
	> Author: 
	> Mail: 
	> Created Time: Tue 16 Jan 2018 11:23:55 PM CST
 ************************************************************************/

#ifndef _THREADLOOP_H
#define _THREADLOOP_H
#include <pthread.h>
#include <event.h>
#include <map>

#include "TcpConnection.h"
using std::map;

class ThreadLoop
{
public:
    typedef void(*event_callback)(TcpConnection*);
public:
    ThreadLoop(const int pipe, event_callback accept, 
               event_callback message, event_callback close) : 
                pipe_fd(pipe), _load(0), accept_cb(accept), 
                message_cb(message), close_cb(close), _base(NULL), thread_id(0) {}

    //~ThreadLoop();

    struct event_base* getBase() { return _base; }
    int getPipe() { return pipe_fd; }
    event_callback getAcceptCallBack() { return accept_cb; }
    event_callback getMessageCallBack() { return message_cb; }
    event_callback getCloseCallBack() { return close_cb; }

    void loadPlus() { ++_load; }
    void loadMinus() { --_load; }
    int getLoad() { return _load; }
    TcpConnection* getConntion(int fd) { return _connection[fd]; }
    void delConntion(int fd) 
    {
        delete _connection[fd];
        _connection.erase(fd);
    }
    map<int, TcpConnection*>* getConntionMap() { return &_connection; }
    void loop();

private:
    int pipe_fd;
    int _load;
    event_callback accept_cb;
    event_callback message_cb;
    event_callback close_cb;
    struct event_base *_base;
    map<int, TcpConnection*> _connection;
    pthread_t thread_id;
};
#endif
