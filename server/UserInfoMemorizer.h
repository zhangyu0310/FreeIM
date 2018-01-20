/*************************************************************************
> File Name: UserInfoMemorizer.h
> Author: 
> Mail: 
> Created Time: 2017/11/30
************************************************************************/
#ifndef _USERINFOMEMORIZER_H
#define _USERINFOMEMORIZER_H
//一个用户信息的链表，模拟数据库的存在。
//应当保证数据的同步性，一致性，也就是输出的结果一定是线程安全的

#include <string>
#define USEREXIST          0
#define USERNOTEXIST       1
#define USERINSERT         2
#define NOTONLINE          3
#define USERONLINE         4
#define NOTOFFLINE         5
#define USEROFFLINE        6
#define PWERROR            7

using std::string;

struct UserNode
{
	bool online;
	UserNode *user_next;
	union
	{
		int fd;
		char *msg;
	};
	union
	{
		UserNode *online_next;
		UserNode *offline_next;
	};
	string name;
	string pw;
};
struct SearchNode
{
	UserNode *prev;
	UserNode *dest;
};
class UserInfoMemorizer
{
public:
	UserInfoMemorizer();
	~UserInfoMemorizer();
	int insertUser(const string &name, const string &pw);
	int userOnline(const int fd, const string &name, const string &pw);
	int userOffline(const string &name);
	bool userIsExist(const string &name, SearchNode &search) const;
	bool userIsOnline(const string &name, SearchNode &search) const;
	bool userIsOffline(const string &name, SearchNode &search) const;
private:
	UserNode* buyUserNode();
	void freeUserNode(UserNode *drop);
	UserNode *userlist_head;
	UserNode *userlist_tail;
	UserNode *onlinelist_head;
	UserNode *onlinelist_tail;
	UserNode *offlinelist_head;
	UserNode *offlinelist_tail;
};

#endif