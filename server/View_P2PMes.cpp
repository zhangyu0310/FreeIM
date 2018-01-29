/*************************************************************************
	> File Name: View_P2PMes.cpp
	> Author: 
	> Mail: 
	> Created Time: Sun 28 Jan 2018 09:11:14 AM CST
 ************************************************************************/

#include "View_P2PMes.h"
#include "TcpConnection.h"
#include "ThreadLoop.h"
#include "DataBase.h"
#include <json/json.h>
#include <string>
#include <map>
using std::map;
using std::string;
using Json::Value;
extern map<pthread_t, DataBase*> db;

void VP2PMes::process(TcpConnection *conn, Value &val)
{
    pthread_t pid = pthread_self();
    map<pthread_t, DataBase*>::iterator it = db.find(pid);
    if(it == db.end())
    {
        exit(1);
    }
    DataBase *database = it->second;

    string from_name = val["from_name"].asString();
    string to_name = val["to_name"].asString();
    string mes = val["message"].asString();

    Value reply;
    reply["type"] = 2;
    int ret = database->P2PMessage(from_name, to_name, mes);
    reply["response"] = ret;

    conn->send(reply.toStyledString());
}
