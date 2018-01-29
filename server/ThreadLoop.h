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
    typedef void(*threads_init_callback)(ThreadLoop*);
public:
    ThreadLoop(const int pipe, const threads_init_callback threads, const event_callback accept, 
               const event_callback message, const event_callback close) : 
                pipe_fd(pipe), _load(0), threads_cb(threads), accept_cb(accept), 
                message_cb(message), close_cb(close), _base(NULL), thread_id(0) {}

    //~ThreadLoop();

    struct event_base* getBase() { return _base; }
    int getPipe() { return pipe_fd; }
    threads_init_callback getThreadsInitCallBack() { return threads_cb; }
    event_callback getAcceptCallBack() { return accept_cb; }
    event_callback getMessageCallBack() { return message_cb; }
    event_callback getCloseCallBack() { return close_cb; }
    pthread_t getThreadID() { return thread_id; }

    void loadPlus() { ++_load; }
    void loadMinus() { --_load; }
    int getLoad() { return _load; }
    TcpConnection* getConntion(const int fd) { return _connection[fd]; }
    void delConntion(const int fd) 
    {
        _connection.erase(fd);
    }
    map<int, TcpConnection*>* getConntionMap() { return &_connection; }
    void loop();

private:
    int pipe_fd;
    int _load;
    threads_init_callback threads_cb;
    event_callback accept_cb;
    event_callback message_cb;
    event_callback close_cb;
    struct event_base *_base;
    map<int, TcpConnection*> _connection;
    pthread_t thread_id;
};
#endif
