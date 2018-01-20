/*************************************************************************
    > File Name: Buffer.cpp
    > Author: 
    > Mail: 
    > Created Time: Wed 10 Jan 2018 07:53:29 PM CST
 ************************************************************************/

#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include "Buffer.h"
#include <string.h>
#include <stdio.h>

string Buffer::getValueAsString(const string &key)
{
    if(_val[key].isString())
    {
        return _val[key].asString();
    }
    else
    {
        return string(NULL);
    }
}
