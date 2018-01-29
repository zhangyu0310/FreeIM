/*************************************************************************
	> File Name: State_Online.h
	> Author: 
	> Mail: 
	> Created Time: Wed 24 Jan 2018 06:37:27 PM CST
 ************************************************************************/

#ifndef _STATE_ONLINE_H
#define _STATE_ONLINE_H
#include "State.h"

class Online : public State
{
public:
    void doAction(Context &context);
    void process();
};
#endif
