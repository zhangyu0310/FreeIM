/*************************************************************************
    > File Name: Buffer.h
    > Author: 
    > Mail: 
    > Created Time: Wed 10 Jan 2018 07:51:17 PM CST
 ************************************************************************/

#ifndef _BUFFER_H
#define _BUFFER_H

#include <json/json.h>
#include <string>
using std::string;
using Json::Value;
using Json::Reader;

class Buffer
{
public:
    Buffer() {}
	Buffer(const string &key, const string &content)
	{
		_val[key] = content;
	}
    Buffer(const Buffer &buf) : _val(buf._val) {}
    Buffer& operator=(const Buffer &buf)
    {
        _val = buf._val;
    }
	~Buffer()
	{
	}
	void addValue(const string &key, const string &content)
	{
		_val[key] = content;
	}
	string getValueAsString(const string &key);
private:
	Value _val;
};

#endif
