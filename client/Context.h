/*************************************************************************
	> File Name: Context.h
	> Author: 
	> Mail: 
	> Created Time: Wed 24 Jan 2018 06:11:02 PM CST
 ************************************************************************/

#ifndef _CONTEXT_H
#define _CONTEXT_H
#include "State.h"

class Context
{
public:
    Context() : _state(NULL) {}
    void setState(State *state)
    { _state = state; }
    void process()
    { _state->process(); }
private:
    State *_state;
};
#endif
