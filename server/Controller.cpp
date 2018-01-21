/*************************************************************************
	> File Name: Controller.cpp
	> Author: 
	> Mail: 
	> Created Time: Sun 21 Jan 2018 11:50:48 PM CST
 ************************************************************************/

#include "Controller.h"
#include <json/json.h>
#include <string>
using std::string;
using Json::Value;
using Json::Reader;

void Controller::process(TcpConnection *conn)
{
    string message = conn->getMessageAsString();
    Reader read;
    Value val;
    read.parse(message, val);

    _control[val["type"].asInt()]->process(conn, val);
}
