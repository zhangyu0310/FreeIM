/*************************************************************************
	> File Name: ThreadLoop.cpp
	> Author: 
	> Mail: 
	> Created Time: Tue 16 Jan 2018 11:32:59 PM CST
 ************************************************************************/

#include "ThreadLoop.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

//#include <iostream>
//using namespace std;

static void read_func(int fd, short event, void *arg);
static void write_func(int fd, short event, void *arg);
static void listen_cb(int fd, short event, void *arg)
{
    ThreadLoop *thiz = (ThreadLoop*)arg;
    thiz->loadPlus();
    map<int, TcpConnection*> *conn = thiz->getConntion();
    char tmp[16] = {0};
    recv(fd, tmp, 16, 0);
    int cli_fd = atoi(tmp);
    TcpConnection *cli_conn = new TcpConnection(cli_fd);
    (*conn)[cli_fd] = cli_conn;

    struct event *cli_event = event_new(thiz->getBase(),
                                        cli_fd, EV_READ,
                                        read_func, arg);
    event_add(cli_event, NULL);
    bzero(&tmp, sizeof(tmp));
    sprintf(tmp, "%d", thiz->getLoad());
    send(fd, tmp, strlen(tmp) + 1, 0);
}

static void* thread_func(void *arg)
{
    ThreadLoop *thiz = (ThreadLoop*)arg; 
    struct event *pipe_event = event_new(thiz->getBase(), 
                                        thiz->getPipe(), 
                                        EV_READ|EV_PERSIST, 
                                        listen_cb, arg);
    event_add(pipe_event, NULL);
    //cout << "thread_func is over " << endl;
    event_base_dispatch(thiz->getBase());
}

static void read_func(int fd, short event, void *arg)
{
    //cout << "in read_func" << endl;
    ThreadLoop *thiz = (ThreadLoop*)arg;
    ThreadLoop::ser_cb read_cb = thiz->getReadCallBack();
    event_base *base = thiz->getBase();
    map<int, TcpConnection*> *conn = thiz->getConntion();
    TcpConnection *connection = (*conn)[fd];
    UserInterface interface(connection);
    read_cb(&interface);

    if(interface.haveWriteEvent())
    {
        //printf("add Write Event\n");
        struct event *write_event = event_new(base, fd, EV_WRITE, write_func, arg);
        event_add(write_event, NULL);
    }
    if(interface.getRet() == INTER_OK)
    {
        struct event *event_again = event_new(base, fd, event, read_func, arg);
        event_add(event_again, NULL);
    }
    else if(interface.getRet() == INTER_CLOSE)
    {
        //TcpConnection 需要删除
        delete connection;
        conn->erase(fd);
        thiz->loadMinus();
    }
    else
    {
        //返回值处理，目前没想到还有什么情况会发生，待定。
    }
}

static void write_func(int fd, short event, void *arg)
{
    ThreadLoop *thiz = (ThreadLoop*)arg;
    ThreadLoop::ser_cb write_cb = thiz->getWriteCallBack();
    event_base *base = thiz->getBase();
    map<int, TcpConnection*> *conn = thiz->getConntion();
    UserInterface interface((*conn)[fd]);
    write_cb(&interface);

    if(interface.getRet() == 1)
    {
        //返回值处理
    }
}

void ThreadLoop::loop()
{
    //cout << "ThreadLoop::loop() is running" << endl;
    if(pipe_fd < 0) return;
    if(read_cb == NULL) return;
    if(write_cb == NULL) return;
    if(_base == NULL)
    {
        _base = event_base_new();
    }
    //cout << "pipe_fd: " << pipe_fd << endl;
    pthread_create(&thread_id, NULL, thread_func, this);
}
