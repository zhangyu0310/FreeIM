/*************************************************************************
	> File Name: View_Register.h
	> Author: 
	> Mail: 
	> Created Time: Mon 22 Jan 2018 12:19:30 AM CST
 ************************************************************************/

#ifndef _VIEW_REGISTER_H
#define _VIEW_REGISTER_H

#include "View.h"
class VRegister : public View
{
public:
    void process(TcpConnection*, Value&);
};
#endif
