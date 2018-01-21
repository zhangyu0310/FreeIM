/*************************************************************************
	> File Name: View_P2PMes.h
	> Author: 
	> Mail: 
	> Created Time: Mon 22 Jan 2018 12:21:10 AM CST
 ************************************************************************/

#ifndef _VIEW_P2PMES_H
#define _VIEW_P2PMES_H

#include "View.h"
class VP2PMes : public View
{
public:
    void process(TcpConnection*, Value&);
};
#endif
