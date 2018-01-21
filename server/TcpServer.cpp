/*************************************************************************
	> File Name: TcpServer.cpp
	> Author: 
	> Mail: 
	> Created Time: Tue 09 Jan 2018 01:48:43 AM CST
 ************************************************************************/

#include "TcpServer.h"

static void change_map(evutil_socket_t fd, short event, void *arg)
{
    TcpServer *thiz = (TcpServer*)arg;
    map<int, int> *load_map = thiz->getMap();
    char tmp[16] = {0};
    recv(fd, tmp, 16, 0);
    (*load_map)[fd] = atoi(tmp);
}

static void accept_func(evutil_socket_t fd, short event, void *arg)
{
    TcpServer *thiz = (TcpServer*)arg;
    map<int, int> *load_map = thiz->getMap();
    map<int, int>::iterator it = load_map->begin();
    std::pair<int, int> min_load = *it;
    for(; it != load_map->end(); ++it)
    {
        if((*it).second < min_load.second)
        {
            min_load = *it;
        }
    }

    struct sockaddr_in cliadd;
    socklen_t len = sizeof(cliadd);
    bzero(&cliadd, sizeof(cliadd));
    int cli_fd = accept(fd, (struct sockaddr*)&cliadd, &len);
    //cout << "accept is over" << endl;
    //TcpServer::event_callback accept_cb = thiz->getAcceptCallBack();
    //TcpConnection conn(cli_fd);
    //accept_cb(&conn);

    char tmp[16] = {0};
    sprintf(tmp, "%d", cli_fd);
    send(min_load.first, tmp, strlen(tmp) + 1, 0);
    //cout << "pipe_fd: " << min_load.first << " cli_fd: " << tmp << endl; 
}

int TcpServer::serverInit()
{
    if(_base != NULL) return SERVER_EXIST;
    if(accept_cb == NULL) return CBFUNC_ERROR;

    _base = event_base_new();

    _sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(_sockfd == -1)
    {
        return FD_ERROR;
    }
   
    struct sockaddr_in saddr;
    bzero(&saddr, sizeof(saddr));
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(_port);
    if(bind(_sockfd, (sockaddr*)&saddr, sizeof(saddr)) == -1)
    {
        return BIND_ERROR;
    }
    
    struct event *listen_event = event_new(_base, _sockfd, EV_READ|EV_PERSIST, accept_func, this);
    if(listen_event == NULL)
    {
        return EVENT_NEW_ERROR;
    }
    event_add(listen_event, NULL);
    
    if(listen(_sockfd, 5) == -1)
    {
        return LISTEN_ERROR;
    }
    int i = 0;
    for(; i < thread_num; ++i)
    {
        int pair[2];
        socketpair(AF_UNIX, SOCK_STREAM, 0, pair);
        self_pair[i] = pair[0];
        threads_pair[i] = pair[1];
        ThreadLoop *thread = new ThreadLoop(self_pair[i], accept_cb, message_cb, close_cb);
        _threads.push_back(thread);
        load_map[threads_pair[i]] = 0;
        struct event *pair_event = event_new(_base, threads_pair[i], EV_READ|EV_PERSIST, change_map, this);
        event_add(pair_event, NULL);
        //cout << "self_pair: "<< self_pair[i] << " threads_pair: " << threads_pair[i] << endl;
    }
    return OK;
}

void TcpServer::run()
{
    vector<ThreadLoop*>::iterator it = _threads.begin();
    for(; it != _threads.end(); ++it)
    {
        (*it)->loop();
        //cout << "TcpServer::run() loop()" << endl;
    }
    event_base_dispatch(_base);
}
