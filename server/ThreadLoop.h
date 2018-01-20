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
#include "UserInterface.h"
#include "TcpConnection.h"
using std::map;

class ThreadLoop
{
public:
    typedef void(*event_cb)(int, short, void*);
    typedef void(*ser_cb)(UserInterface*);
public:
    ThreadLoop(const int pipe) : pipe_fd(pipe), _load(0),
                        read_cb(NULL), write_cb(NULL), _base(NULL), thread_id(0) {}
    ThreadLoop(const int pipe, ser_cb rcb, ser_cb wcb) : pipe_fd(pipe), _load(0),
                        read_cb(rcb), write_cb(wcb), _base(NULL), thread_id(0) {}

    //~ThreadLoop();
    void addReadCallBack(ser_cb cb) { read_cb = cb; }
    void addWriteCallBack(ser_cb cb) { write_cb = cb; }
    struct event_base* getBase() { return _base; }
    int getPipe() { return pipe_fd; }
    ser_cb getReadCallBack() { return read_cb; }
    ser_cb getWriteCallBack() { return write_cb; }
    void loadPlus() { ++_load; }
    void loadMinus() { --_load; }
    int getLoad() { return _load; }
    map<int, TcpConnection*>* getConntion() { return &_connection; }
    void loop();

private:
    int pipe_fd;
    int _load;
    ser_cb read_cb;
    ser_cb write_cb;
    struct event_base *_base;
    map<int, TcpConnection*> _connection;
    pthread_t thread_id;
};
#endif
