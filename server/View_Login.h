/*************************************************************************
	> File Name: View_Login.h
	> Author: 
	> Mail: 
	> Created Time: Mon 22 Jan 2018 12:21:10 AM CST
 ************************************************************************/

#ifndef _VIEW_LOGIN_H
#define _VIEW_LOGIN_H

#include "View.h"
class VLogin : public View
{
public:
    void process(TcpConnection*, Value&);
};
#endif
