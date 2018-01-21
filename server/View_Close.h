/*************************************************************************
	> File Name: View_Close.h
	> Author: 
	> Mail: 
	> Created Time: Mon 22 Jan 2018 12:21:10 AM CST
 ************************************************************************/

#ifndef _VIEW_CLOSE_H
#define _VIEW_CLOSE_H

#include "View.h"
class VClose : public View
{
public:
    void process(TcpConnection*, Value&);
};
#endif
