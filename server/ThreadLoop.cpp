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

static void message_func(int fd, short event, void *arg);
static void listen_cb(int fd, short event, void *arg)
{
    ThreadLoop *thiz = (ThreadLoop*)arg;
    thiz->loadPlus();

    //能否修改这部分
    map<int, TcpConnection*> *conn = thiz->getConntionMap();
    char tmp[16] = {0};
    recv(fd, tmp, 16, 0);
    int cli_fd = atoi(tmp);
    TcpConnection *cli_conn = new TcpConnection(cli_fd, thiz);
    ThreadLoop::event_callback close_cb = thiz->getCloseCallBack();
    if(close_cb != NULL)
    {
        cli_conn->addCloseCallBack(close_cb);
    }
    (*conn)[cli_fd] = cli_conn;
    ThreadLoop::event_callback accept_cb = thiz->getAcceptCallBack();
    accept_cb(cli_conn);

    struct event *cli_event = event_new(thiz->getBase(),
                                        cli_fd, EV_READ,
                                        message_func, arg);
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

static void message_func(int fd, short event, void *arg)
{
    //cout << "in read_func" << endl;
    ThreadLoop *thiz = (ThreadLoop*)arg;
    ThreadLoop::event_callback message_cb = thiz->getMessageCallBack();
    event_base *base = thiz->getBase();

    //修改
    //map<int, TcpConnection*> *conn = thiz->getConntionMap();
    TcpConnection *connection = thiz->getConntion(fd);
    if(connection->recv() <= 0)
    {
        connection->close();
        delete connection;
    }
    else
    {
        message_cb(connection);
        if(connection->isClosed())
        {
            delete connection;
        }
        else
        {
            struct event *event_again = event_new(base, fd, event, message_func, arg);
            event_add(event_again, NULL);
        }
    }
}

void ThreadLoop::loop()
{
    //cout << "ThreadLoop::loop() is running" << endl;
    if(pipe_fd < 0) return;
    if(message_cb == NULL) return;
    if(_base == NULL)
    {
        _base = event_base_new();
    }
    //cout << "pipe_fd: " << pipe_fd << endl;
    pthread_create(&thread_id, NULL, thread_func, this);
}
