/*************************************************************************
	> File Name: FreeIM.cpp
	> Author: 
	> Mail: 
	> Created Time: Mon 29 Jan 2018 01:06:48 PM CST
 ************************************************************************/

#include <iostream>
#include <sys/epoll.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <string>
#include <stdio.h>
using namespace std;

int main()
{
    printf("\033[2J");
    int input;
    string username;
    string pw;
    bool online = 0;
    char _ip[] = "120.24.89.156";
    int _port = 1219;

    int _sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(_sockfd == -1) return -1;

    struct sockaddr_in saddr;
    bzero(&saddr, sizeof(saddr));
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(_port);
    inet_pton(AF_INET, _ip, &saddr.sin_addr);
    
    int epfd = epoll_create(5);
    struct epoll_event event;
    event.events = EPOLLIN|EPOLLET;
    event.data.fd = 0;
    epoll_ctl(epfd, EPOLL_CTL_ADD, 0, &event);
    //event.data.fd = 1;
    //epoll_ctl(epfd, EPOLL_CTL_ADD, 1, &event);
    event.data.fd = _sockfd;
    epoll_ctl(epfd, EPOLL_CTL_ADD, _sockfd, &event);

    int ret = connect(_sockfd, (struct sockaddr*)&saddr, sizeof(saddr));
    if(ret == -1) return -1;

    event.data.fd = 1;
    event.events = EPOLLOUT|EPOLLET;
    epoll_ctl(epfd, EPOLL_CTL_ADD, 1, &event);

    struct epoll_event events[4];
    while(1)
    {
        int ret = epoll_wait(epfd, events, 4, -1);
        for(int i = 0; i < ret; ++i)
        {
            int fd = events[i].data.fd;
            if(fd == 1)
            {
                if(!online)
                {
                    cout << "0 --- Exit  ---" << endl;
                    cout << "1 --- Login  ---" << endl;
                    cout << "2 --- Logon ---" << endl;
                    cout << "Select: ";
                }
                else
                {
                    printf("\033[2J");
                    printf("\033[3;0H");
                    cout << "0 --- Exit   ---" << endl;
                    cout << "1 --- Send   ---" << endl;
                    cout << "2 --- Radio  ---" << endl;
                    cout << "3 --- Logout ---" << endl;
                    cout << "Select: ";
                }
                struct epoll_event event;
                event.events = EPOLLET;
                epoll_ctl(epfd, EPOLL_CTL_MOD, fd, &event);
            }
            else if(fd == 0)
            {
                if(input )
                cin >> input;
            }
        }
    }
}
