/*************************************************************************
> File Name: UserInfoHandler.h
> Author: 
> Mail: 
> Created Time: 2017/11/30
************************************************************************/
#ifndef _USERINFOHANDLER_H
#define _USERINFOHANDLER_H
//负责处理用户信息，使用户信息真实的存储单元被隐藏。
//不考虑线程安全，默认底层提供的数据是可靠的。
#include <string>
using std::string;
class UserNode;
struct UserInfo
{
	bool online;
	union
	{
		int fd;
		char **usermsg;
	};
};
class UserInfoMemorizer;
class UserInfoHandler
{
public:
	static UserInfoHandler& getInstance()
	{
		return handler;
	}
	int userLogon(int fd, const string &name, const string &pw);
	int userLogin(int fd, const string &name, const string &pw);
	int userLogoff(int fd, const string &name);
	UserInfo getUserInfo(const string &name);
private:
	UserInfoHandler();
	//bool compUserID(const string &userid);
	//bool compUserPW(const string &pw);
	static UserInfoHandler handler;
	UserInfoMemorizer *_memorizer;
};

#endif