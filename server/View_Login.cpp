/*************************************************************************
	> File Name: View_Login.cpp
	> Author: 
	> Mail: 
	> Created Time: Thu 25 Jan 2018 08:45:56 PM CST
 ************************************************************************/

#include "View_Login.h"
#include "TcpConnection.h"
#include "ThreadLoop.h"
#include "DataBase.h"
#include <json/json.h>
#include <string>
#include <map>
using std::string;
using Json::Value;
using std::map;
extern map<pthread_t, DataBase*> db;

void VLogin::process(TcpConnection *conn, Value &val)
{
    pthread_t pid = conn->getThreadLoop()->getThreadID();
    map<pthread_t, DataBase*>::iterator it = db.find(pid);
    DataBase *database;
    if(it != db.end())
    {
        database = it->second;
    }
    else
    {
        exit(1);
    }

    string user_name = val["username"].asString();
    string pw = val["password"].asString();

    Value reply;
    reply["type"] = 1;
    int ret = database->UserLogin(user_name, pw, conn->getConnfd()); 
    reply["response"] = ret;

    conn->send(reply.toStyledString());
}
