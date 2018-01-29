/*************************************************************************
	> File Name: FreeIM_Client.cpp
	> Author: 
	> Mail: 
	> Created Time: Wed 24 Jan 2018 05:57:58 PM CST
 ************************************************************************/

#include "FreeIM_Client.h"
#include <string>
#include <stdlib.h>
#include <iostream>
#include <json/json.h>
using namespace std;
typedef enum{ Online, Offline } State;
extern State state;
extern string username;
extern string pw;
extern int input;
extern string to_user;
extern string send_message;

using Json::Value;
using Json::Reader;
void Offline_Select();
void Online_Select();

void Offline_Send(TcpConnection *conn)
{ 
    if(state == Online)
    {
        cout << "Connect Error!" << endl;
        exit(1);
    }
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
    if(state == Offline)
    {
        cout << "Connect Error!" << endl;
        exit(1);
    }
    Value val;
    if(input == 1)
    {
        val["type"] = MSG_TYPE_P2PMES;
        val["username"] = to_user;
    }
    else if(input == 2)
    {
        val["type"] = MSG_TYPE_GROUP;
        val["username"] = username;
    }
    else
    {
        cout << "没实现呢？" <<endl;
    }
    val["message"] = send_message;

    conn->send(val.toStyledString());
}

void connect_cb(TcpConnection *conn)
{
    Offline_Send(conn);
}

void message_cb(TcpConnection *conn)
{
    string res = conn->getMessageAsString();
    Reader read;
    Value val;
    read.parse(res, val);
    int type = val["type"].asInt();
    int ret = 0;
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
        Offline_Select();
        Offline_Send(conn);
        break;
    case MSG_TYPE_LOGIN:
        ret = val["response"].asInt();

        switch(ret)
        {
        case 0:
            cout << "Logon success!" << endl;
            state = Online;
            Online_Select();
            Online_Send(conn);
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
        if(ret != 0)
        {
            Offline_Select();
            Offline_Send(conn); 
        }
        break;
    case MSG_TYPE_GROUP:
    case MSG_TYPE_P2PMES:
        {
            string name = val["username"].asString();
            string mes = val["message"].asString();
            cout << "From: " << name << " Message: ";
            cout << mes << endl;
        }
        break;
    default:
        break;
    }
}

void close_cb(TcpConnection *conn)
{
    cout << "Server is closed!" << endl;
    exit(0);
}
