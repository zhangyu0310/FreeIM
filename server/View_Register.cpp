/*************************************************************************
	> File Name: View_Register.cpp
	> Author: 
	> Mail: 
	> Created Time: Mon 22 Jan 2018 05:23:55 PM CST
 ************************************************************************/

#include "View_Register.h"
#include "TcpConnection.h"
#include "DataBase.h"
#include "ThreadLoop.h"
#include <map>
#include <json/json.h>
#include <string>
using std::string;
using std::map;
using Json::Value;
extern map<pthread_t, DataBase*> db;

void VRegister::process(TcpConnection *conn, Value &val)
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
    reply["type"] = 0;
    if(database->registerUser(user_name, pw) == REGISTER_FAIL)
    {
        reply["response"] = 0;
    }
    else
    {
        reply["response"] = 1;
    }
    
    conn->send(reply.toStyledString());
}
