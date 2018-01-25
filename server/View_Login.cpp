/*************************************************************************
	> File Name: View_Login.cpp
	> Author: 
	> Mail: 
	> Created Time: Thu 25 Jan 2018 08:45:56 PM CST
 ************************************************************************/

#include "View_Login.h"
#include "TcpConnection.h"
#include "DataBase.h"
#include <json/json.h>
#include <string>
using std::string;
using Json::Value;
extern DataBase db;

void VLogin::process(TcpConnection* conn, Value& val)
{
    string user_name = val["username"].asString();
    string pw = val["password"].asString();

    Value reply;
    int ret = db.UserLogin(user_name, pw, conn->getConnfd()); 
    reply["response"] = ret;

    conn->send(reply.toStyledString());
}
