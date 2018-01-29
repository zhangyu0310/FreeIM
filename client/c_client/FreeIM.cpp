/*************************************************************************
	> File Name: FreeIM.cpp
	> Author: 
	> Mail: 
	> Created Time: Mon 29 Jan 2018 02:19:48 PM CST
 ************************************************************************/

#include <iostream>
#include <pthread.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <stdio.h>
#include <json/json.h>
#include <event.h>
#include <map>
#include "TcpConnection.h"
using namespace std;
using Json::Value;
using Json::Reader;

enum
{
    MSG_TYPE_REGISTER = 0,
    MSG_TYPE_LOGIN    = 1,
    MSG_TYPE_P2PMES   = 2,
    MSG_TYPE_GROUP    = 3,
    MSG_TYPE_LIST     = 4,
    MSG_TYPE_CLOSE    = 5,
    MSG_TYPE_LOGOUT   = 6
};

int _sockfd;
int input;
string username;
string pw;
string to_user;
string send_message;
bool online = 0;
bool have_mes = 0;
bool to_yourself = 0;
bool once = 0;
bool no_user = 0;
const char _ip[] = "120.24.89.156";
const int _port = 1219;
map<string, string> mes_map;

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
//pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;

void Offline_Send(TcpConnection *conn);
void Online_Send(TcpConnection *conn);
void Offline_Select();
void Online_Select(TcpConnection *conn);
void* thread_func(void *);
void message_func(int, short, void*);
void Off_On_Send(int, short, void*);

int main()
{
    printf("\033[2J");
    printf("\033[1;0H");

    _sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(_sockfd == -1) return -1;

    struct sockaddr_in saddr;
    bzero(&saddr, sizeof(saddr));
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(_port);
    inet_pton(AF_INET, _ip, &saddr.sin_addr);
    
    int ret = connect(_sockfd, (struct sockaddr*)&saddr, sizeof(saddr));
    if(ret == -1) return -1;
    TcpConnection conn(_sockfd);
    pthread_t pid;
    pthread_create(&pid, NULL, thread_func, NULL);

    struct event_base *base = event_base_new();
    struct event *input_event = event_new(base, 0, EV_READ|EV_PERSIST, Off_On_Send, &conn);
    event_add(input_event, NULL);

    while(1)
    {
        pthread_mutex_lock(&mutex1);
        if(!online)
        {
            Offline_Select();
            Offline_Send(&conn);
        }
        else
        {
            Online_Select(&conn);
        }
    }
}

void Offline_Select()
{ 
    while(1)
    {
        cout << "0 --- Exit  ---" << endl;
        cout << "1 --- Login  ---" << endl;
        cout << "2 --- Logon ---" << endl;
        cout << "Select: ";
        cin >> input;
        if(input == 0 || input == 1 || input == 2)
            break;
        cout << "Select error, input again" << endl;
    }
    if(input == 0) 
    {
        printf("\033[2J");
        printf("\033[1;0H");
        cout << "Bye!" << endl;
        exit(0);
    }
    cout << "Input user name: ";
    cin >> username;
    cout << "Input password: ";
    cin >> pw;
}

void Online_Select(TcpConnection *conn)
{
    printf("\033[2J");
    while(1)
    {
        printf("\033[2;0H");
        if(once == 0)
        {
            cout << "Logon success!" << endl;
            once = 1;
        }
        if(to_yourself == 1)
        {
            cout << "Can't send message to your self!" << endl;
            to_yourself = 0;
        }
        if(no_user == 1)
        {
            cout << "User is non_existent" << endl;
            no_user = 0;
        }
        if(input == 4)
        {
            map<string, string>::iterator it = mes_map.begin();
            cout << "Message List:" << endl;
            for(; it != mes_map.end(); ++it)
            {
                cout << "From: " << it->first << " Message: " << it->second << endl;
            }
            cout << endl;
            have_mes = 0;
        }
        if(have_mes)
        {
            printf("\033[s");
            printf("\033[1;0H");
            printf("\033[1;31m\033[5mYou have new message!");
            printf("\033[0m");
            printf("\033[u");
        }
        cout << "0 ---      Exit      ---" << endl;
        cout << "1 ---      Send      ---" << endl;
        cout << "2 ---      Radio     ---" << endl;
        cout << "3 ---     Logout     ---" << endl;
        cout << "4 --- Check Message  ---" << endl;
        cout << "5 ---     ReFresh    ---" << endl;
        cout << "Select: ";
        cin >> input;
        if(input == 0)
        {
            printf("\033[2J");
            printf("\033[1;0H");
            cout << "Bye!" << endl;
            exit(0);
        }
        if(input == 5)
        {
            pthread_mutex_unlock(&mutex1);
            return;
        }
        if(input == 1 || input == 2 || input == 3 || input == 4)
            break;
        cout << "Select error, input again" << endl;
    }
    if(input == 1)
    {
        cout << "To: ";
        cin >> to_user;
        if(to_user.compare(username) == 0)
        {
            to_yourself = 1;
            pthread_mutex_unlock(&mutex1);
            return;
        }
        cout << "Input your message: " << endl;
        cin >> send_message;
    }
    else if(input == 2)
    {
        cout << "Input your message: " << endl;
        cin >> send_message;
    }
    else if(input == 4)
    {
        pthread_mutex_unlock(&mutex1);
        return;
    }
    Online_Send(conn);
}

void* thread_func(void *arg)
{
    struct event_base *base = event_base_new();
    struct event *recv_event = event_new(base, _sockfd, EV_READ|EV_PERSIST, message_func, base);
    event_add(recv_event, NULL);
    event_base_dispatch(base);
}

void Offline_Send(TcpConnection *conn)
{ 
    Value val;
    if(input == 1)
        val["type"] = MSG_TYPE_REGISTER;
    else if(input == 2)
        val["type"] = MSG_TYPE_LOGIN;
    else 
    {
        cout << "Connect Error!" << endl;
        exit(1);
    }

    val["username"] = username;
    val["password"] = pw;

    conn->send(val.toStyledString());
}

void Online_Send(TcpConnection *conn)
{
    Value val;
    if(input == 1)
    {
        val["type"] = MSG_TYPE_P2PMES;
        val["from_name"] = username;
        val["to_name"] = to_user;
        val["message"] = send_message;
    }
    else if(input == 2)
    {
        val["type"] = MSG_TYPE_GROUP;
        val["username"] = username;
        val["message"] = send_message;
    }
    else if(input == 3)
    {
        val["type"] = MSG_TYPE_LOGOUT;
    }
    else
    {
        return;
    }

    conn->send(val.toStyledString());
}

void message_func(int fd, short event, void *arg)
{
    //非阻塞与ET，需要确保消息完整，之后修改
    char tmp[128] = {0};
    recv(_sockfd, tmp, 128, 0);
    string mes(tmp);
    
    int ret;
    Reader read;
    Value val;
    read.parse(mes, val);
    int type = val["type"].asInt();
    switch(type)
    {
    case MSG_TYPE_REGISTER:
        if(val["response"].asInt())
        {
            cout << "Register success!" << endl;
        }
        else
        {
            cout << "Register failed!" << endl;
        }
        break;
    case MSG_TYPE_LOGIN:
        ret = val["response"].asInt();

        switch(ret)
        {
        case 0:
            online = 1;
            break;
        case 2:
            cout << "Logon failed!" << endl;
            break;
        case 3:
            cout << "User is Non_existent!" << endl;
            break;
        case 4:
            cout << "User Name is Error!" << endl;
            break;
        case 5:
            cout << "Password is Error!" << endl;
            break;
        case 6:
            cout << "The User is onlined" << endl;
            break;
        }
        break;
    case MSG_TYPE_GROUP:
    case MSG_TYPE_P2PMES:
        if(val["response"].isInt())
        {
            if(val["response"].asInt() == 3)
            {
                no_user = 1;
            }
        }
        else
        {
            string name = val["from_name"].asString();
            string mes = val["message"].asString();
            mes_map[name] = mes;
            have_mes = 1;
        }
        break;
    case MSG_TYPE_LOGOUT:
        online = 0;
        printf("\033[2J");
        printf("\033[1;0H");
        cout << username << " is Logout!" << endl;
    case MSG_TYPE_CLOSE:
        printf("\033[2J");
        printf("\033[1;0H");
        cout << username << " is Logon on another places" << endl;
        exit(1);
    }
    pthread_mutex_unlock(&mutex1);
}
