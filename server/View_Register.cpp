/*************************************************************************
	> File Name: View_Register.cpp
	> Author: 
	> Mail: 
	> Created Time: Mon 22 Jan 2018 05:23:55 PM CST
 ************************************************************************/

#include "View_Register.h"
#include "TcpConnection.h"
#include "DataBase.h"
#include <json/json.h>
#include <string>
using std::string;
using Json::Value;
extern DataBase db;

void VRegister::process(TcpConnection *conn, Value &val)
{
    string user_name = val["username"].asString();
    string pw = val["password"].asString();

    Value reply;
    if(db.registerUser(user_name, pw) == REGISTER_FAIL)
    {
        reply["response"] = 0;
    }
    else
    {
        reply["response"] = 1;
    }
    
    conn->send(reply.toStyledString());
}
