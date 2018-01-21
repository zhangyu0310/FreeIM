/*************************************************************************
	> File Name: UserInterface.h
	> Author: 
	> Mail: 
	> Created Time: Wed 17 Jan 2018 02:11:03 AM CST
 ************************************************************************/

#ifndef _USERINTERFACE_H
#define _USERINTERFACE_H
#include <event.h>
#include "TcpConnection.h"

#define INTER_OK        0
#define INTER_CLOSE     1

class UserInterface
{
public:
    UserInterface(TcpConnection *conn) : _conn(conn), _write(false), _ret(INTER_OK) {}

    int getFileDescriptor() { return _conn->getConnfd(); }
    int getRet() { return _ret; }
    TcpConnection* getConnection() { return _conn; }
    void writeEvent()
    {
        _write = true;
    }
    void writeEvent(const Value &val) 
    { 
        _write = true;
        _conn->setValue(val);
    }
    void close() 
    {
        _conn->close();
        _ret = INTER_CLOSE;
    }
    bool haveWriteEvent() { return _write == 1; }
private:
    bool _write;
    TcpConnection *_conn;
    int _ret;
};
#endif
