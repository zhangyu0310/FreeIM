/*************************************************************************
	> File Name: FreeIM_Server.cpp
	> Author: 
	> Mail: 
	> Created Time: Mon 22 Jan 2018 12:34:51 AM CST
 ************************************************************************/

#include "FreeIM_Server.h"
#include "Controller.h"
#include "View_All.h"
#include <iostream>
#include <map>
#include "DataBase.h"
using std::cout;
using std::endl;
std::map<pthread_t, DataBase*> db;

void threads_cb(ThreadLoop *loop)
{
    pthread_t pid = pthread_self();
    DataBase *tmp = new DataBase;
    db[pid] = tmp;
}

void accept_func(TcpConnection *conn)
{
    cout << "FD: " << conn->getConnfd() << " is accepted!" << endl;
}
void message_func(TcpConnection *conn)
{  
    Controller &control = Controller::getInstance();
    control.process(conn);
}
void close_func(TcpConnection *conn)
{
    pthread_t pid = pthread_self();
    map<pthread_t, DataBase*>::iterator it = db.find(pid);
    if(it != db.end())
    {
        it->second->UserLogout(conn->getConnfd());
    }
    else
    {
        exit(1);
    }
    cout << "FD: " << conn->getConnfd() << " is closed!" << endl;
}

void FreeIM::init()
{
    Controller &control = Controller::getInstance();
    control.registerView(MSG_TYPE_REGISTER, new VRegister);
    control.registerView(MSG_TYPE_LOGIN,    new VLogin);
    control.registerView(MSG_TYPE_P2PMES,   new VP2PMes);
    control.registerView(MSG_TYPE_CLOSE,    new VClose);
    _server.serverInit();
}

void FreeIM::run()
{
    _server.run();
}
