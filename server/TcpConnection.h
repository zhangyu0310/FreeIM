/*************************************************************************
	> File Name: TcpConnection.h
	> Author: 
	> Mail: 
	> Created Time: Sun 14 Jan 2018 01:33:27 PM CST
 ************************************************************************/

#ifndef _TCPCONNECTION_H
#define _TCPCONNECTION_H
#include <json/json.h>
#include <string>
using std::string;
using Json::Value;

class TcpConnection
{
public:
    TcpConnection(int sockfd) : conn_fd(sockfd) {}
    //~TcpConnection();
    int getConnfd() { return conn_fd; }

    Value& getValue() { return _val; }
    string getValueAsString(string key);
    int getValueAsInt(string key);
    void setValue(Value val) { _val = val; }
    bool isString(string key) { return _val[key].isString(); }
    bool isNull(string key) { return _val[key].isNull(); }
    bool isInt(string key) { return _val[key].isInt(); }

    void send();
    void send(Value &buf);
    int recv();
    void close();
private:
    int conn_fd;
    Value _val;
};
#endif
