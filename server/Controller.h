/*************************************************************************
	> File Name: Controller.h
	> Author: 
	> Mail: 
	> Created Time: Sun 21 Jan 2018 11:21:42 PM CST
 ************************************************************************/

#ifndef _CONTROLLER_H
#define _CONTROLLER_H

#include "View.h"
#include <map>
using std::map;

class Controller
{
public:
    static Controller& getInstance()
    {
        static Controller controller;
        return controller;
    }

    void registerView(int num, View* view) 
    {
        _control[num] = view;
    }

    void cancelView(int num)
    {
        View *view = _control[num];
        delete view;
        _control.erase(num);
    }

    void process(TcpConnection *conn);
private:
    Controller();
    Controller(const Controller&);
    map<int, View*> _control;
};

#endif
