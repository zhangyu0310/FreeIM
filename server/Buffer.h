/*************************************************************************
    > File Name: Buffer.h
    > Author: 
    > Mail: 
    > Created Time: Wed 10 Jan 2018 07:51:17 PM CST
 ************************************************************************/

#ifndef _BUFFER_H
#define _BUFFER_H

#include <string>
using std::string;

class Buffer
{
public:
    Buffer() {}
    Buffer(const string &str) : _buffer(str) {}
    void setMessage(const string &message) { _buffer = message; }
    string getMessageAsString() { return _buffer; }
    const char* getMessageAsCstr() { return _buffer.c_str(); }
    int size() { return _buffer.size(); }
private:
    string _buffer;
};

#endif
