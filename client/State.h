/*************************************************************************
	> File Name: State.h
	> Author: 
	> Mail: 
	> Created Time: Wed 24 Jan 2018 06:11:31 PM CST
 ************************************************************************/

#ifndef _STATE_H
#define _STATE_H

class Context;
class State
{
public:
    virtual void doAction(const Context &context) = 0;
};
#endif
