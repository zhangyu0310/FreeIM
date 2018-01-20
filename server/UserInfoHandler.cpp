/*************************************************************************
> File Name: UserInfoHandler.cpp
> Author: 
> Mail: 
> Created Time: 2017/12/01
************************************************************************/
#include "UserInfoHandler.h"
#include "UserInfoMemorizer.h"
#include <sys/socket.h>
#include <iostream>
#include <stdexcept>
#include <new>

UserInfoHandler::UserInfoHandler()
{
	try
	{
		_memorizer = new UserInfoMemorizer();
	}
	catch(std::bad_alloc &e)
	{
		std::cout << e.what() << std::endl;
	}
}

int UserInfoHandler::userLogon(int fd, const string &name, const string &pw)
{
	int ret = _memorizer->insertUser(name, pw);
	if(ret == USEREXIST)
	{
		char tmp[] = "UserID is duplicate";
		send(fd, tmp, sizeof(tmp), 0);
	}
	return ret;
}

int UserInfoHandler::userLogin(int fd, const string &name, const string &pw)
{
	int ret = _memorizer->userOnline(fd, name, pw);
	if(ret != USERONLINE)
	{
        SearchNode search;
		if((ret = _memorizer->userIsOnline(name, search)) == true)
		{
			char tmp[] = "UserID is already online";
			send(fd, tmp, sizeof(tmp), 0);
			ret = NOTOFFLINE;
		}
		else
		{
			char tmp[] = "UserID is Non-existent";
			send(fd, tmp, sizeof(tmp), 0);
			ret = USERNOTEXIST;
		}
	}
	else if(ret == PWERROR)
	{
		char tmp[] = "Password have mistake";
		send(fd, tmp, sizeof(tmp), 0);
	}
	return ret;
}

int UserInfoHandler::userLogoff(int fd, const string &name)
{
	int ret = _memorizer->userOffline(name);
	if(ret != USEROFFLINE)
	{
        throw std::runtime_error("UserInfo not in the userOnline_list");
	}
	return ret;
}

UserInfo UserInfoHandler::getUserInfo(const string &name)
{
	SearchNode search;
    int ret = _memorizer->userIsExist(name, search);
    UserInfo info;
	if(ret == USERNOTEXIST)
    {
        info.online = 0;
        info.fd = -1;
    }
	else if(search.dest->online)
	{
		info.online = 1;
		info.fd = search.dest->fd;
	}
	else
	{
		info.online = 0;
		info.usermsg = &(search.dest->msg);
	}
	return info;
}
