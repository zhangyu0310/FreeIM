/*************************************************************************
	> File Name: State_Offline.cpp
	> Author: 
	> Mail: 
	> Created Time: Wed 24 Jan 2018 06:45:52 PM CST
 ************************************************************************/
#include <iostream>
#include <string>
#include <json/json.h>
#include <stdlib.h>
#include "State_Offline.h"
#include "Context.h"
#include "TcpConnection.h"
using namespace std;

void Offline::doAction(Context &context)
{
    context.setState(this);
    cout << "0 --- Exit  ---" << endl;
    cout << "1 --- Login ---" << endl;
    cout << "2 --- Logon ---" << endl;
}

void Offline::sendRequest(TcpConnection *conn)
{
    do{
        cout << "Input: ";
        cin >> _input;
    }while(_input != 0 && _input != 1 && _input != 2);
    if(_input == 0)
    {
        exit(0);
    }
    else if(_input == 1 || _input == 2)
    {
        string username;
        string pw;
        cout << "Input user name: ";
        cin >> username;
        cout << "Input password:";
        cin >> pw;
        Json::Value val;
        if(_input == 1) val["type"] = 0;
        if(_input == 2) val["type"] = 1;
        val["username"] = username;
        val["password"] = pw;
        conn->send(val.toStyledString());
    }
}

int Offline::recvResponse(TcpConnection *conn)
{
    string response = conn->getMessageAsString();
    Json::Reader read;
    Json::Value val;
    read.parse(response, val);
    if(val["response"].asInt() == 0) 
    {
        if(_input == 1)
        {
            cout << "register failed" << endl;
        }
    }
    else
    {
        if()
    }
}
