/*************************************************************************
	> File Name: View_Close.cpp
	> Author: 
	> Mail: 
	> Created Time: Mon 29 Jan 2018 03:56:27 PM CST
 ************************************************************************/

#include "View_Close.h"
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

void VClose::process(TcpConnection *conn, Value& val)
{
    pthread_t pid = pthread_self();
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

    int ret = database->UserLogout(conn->getConnfd());
    conn->close();
}
