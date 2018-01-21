/*************************************************************************
	> File Name: View.h
	> Author: 
	> Mail: 
	> Created Time: Sun 21 Jan 2018 11:16:39 PM CST
 ************************************************************************/

#ifndef _VIEW_H
#define _VIEW_H

#include <json/json.h>
#include "TcpConnection.h"
using Json::Value;

class View
{
public:
    virtual void process(TcpConnection*, Value&) = 0;
};

#endif
