/*************************************************************************
> File Name: UserInfoMemorizer.cpp
> Author: 
> Mail: 
> Created Time: 2017/11/30
************************************************************************/
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <iostream>
#include <exception>
#include "UserInfoMemorizer.h"

UserNode* UserInfoMemorizer::buyUserNode()
{
    UserNode *tmp = NULL;
	try
	{
		tmp = new UserNode();
	}
	catch(const std::bad_alloc &e)
	{
		std::cout << "bad_alloc" << e.what() << std::endl;
	}
	bzero(tmp, sizeof(UserNode));
	return tmp;
}

void UserInfoMemorizer::freeUserNode(UserNode *drop)
{
	if(drop == NULL)
		return;
	delete drop;
	drop = NULL;
}

UserInfoMemorizer::UserInfoMemorizer()
{
	userlist_head = buyUserNode();
	userlist_tail = userlist_head;
	
	onlinelist_head = buyUserNode();
	onlinelist_tail = onlinelist_head;
	
	offlinelist_head = buyUserNode();
	offlinelist_tail = offlinelist_head;
}

UserInfoMemorizer::~UserInfoMemorizer()
{
	UserNode *drop = userlist_head->user_next;
	UserNode *tmp = drop->user_next;
	while(drop != NULL)
	{
		UserNode *tmp = drop->user_next;
		freeUserNode(drop);
		drop = tmp;
	}
	freeUserNode(userlist_head);
	freeUserNode(onlinelist_head);
	freeUserNode(offlinelist_head);
}

int UserInfoMemorizer::insertUser(const string &name, const string &pw)
{
	SearchNode search;
    if(userIsExist(name, search))
	{
		return USEREXIST;
	}
	userlist_tail->user_next = buyUserNode();
	userlist_tail = userlist_tail->user_next;
	offlinelist_tail->offline_next = userlist_tail;
	offlinelist_tail = offlinelist_tail->offline_next;
	userlist_tail->name = name;
	userlist_tail->pw = pw;
	return USERINSERT;
}

int UserInfoMemorizer::userOnline(const int fd, const string &name, const string &pw)
{
	SearchNode search;
	if(userIsOffline(name, search))
	{
		return NOTOFFLINE;
	}
	if(search.dest->pw != pw)
	{
		return PWERROR;
	}
	search.prev->offline_next = search.dest->offline_next;
	char *sendmes = search.dest->msg;
	if(sendmes != NULL)
	{
		//How to deal with the message?
		send(fd, sendmes, 256, 0);
	}
	search.dest->online = true;
	search.dest->fd = fd;
	onlinelist_tail->online_next = search.dest;
	search.dest->online_next = NULL;
	return USERONLINE;
}

int UserInfoMemorizer::userOffline(const string &name)
{
	SearchNode search;
	if(userIsOnline(name, search))
	{
		return NOTONLINE;
	}
	search.prev->online_next = search.dest->online_next;
	search.dest->online = false;
	search.dest->msg = NULL;
	offlinelist_tail->offline_next = search.dest;
	search.dest->offline_next = NULL;
	return USEROFFLINE;
}

bool UserInfoMemorizer::userIsExist(const string &name,
									 SearchNode &search) const
{
	search.dest = userlist_head->user_next;
	search.prev = userlist_head;
	for(; search.dest != NULL; search.dest = search.dest->user_next)
	{
		if(search.dest->name == name)
		{
			return true;
		}
		search.prev = search.dest;
	}
	return false;
}

bool UserInfoMemorizer::userIsOnline(const string &name, 
									SearchNode &search) const
{
	search.dest = onlinelist_head->online_next;
	search.prev = onlinelist_head;
	for(; search.dest != NULL; search.dest = search.dest->online_next)
	{
		if(search.dest->name == name)
		{
			return true;
		}
		search.prev = search.dest;
	}
	return false;
}

bool UserInfoMemorizer::userIsOffline(const string &name, 
									SearchNode &search) const
{
	search.dest = offlinelist_head->offline_next;
	search.prev = offlinelist_head;
	for(; search.dest != NULL; search.dest = search.dest->offline_next)
	{
		if(search.dest->name == name)
		{
			return true;
		}
		search.prev = search.dest;
	}
	return false;
}
