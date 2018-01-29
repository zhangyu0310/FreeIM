/*************************************************************************
	> File Name: DataBase.h
	> Author: 
	> Mail: 
	> Created Time: Mon 22 Jan 2018 05:31:51 PM CST
 ************************************************************************/

#ifndef _DATABASE_H
#define _DATABASE_H
#include "SQL.h"
#include <stdlib.h>

#define DATABASE_OK        0
#define REGISTER_FAIL      1
#define LOGIN_FAIL         2
#define NON_EXISTENT       3
#define NAME_ERROR         4
#define PASSWORD_ERROR     5
#define USER_IS_ONLINE     6
#define CLOSE_FAIL         7

const char message_store[] = "/root/tulun/project/FreeIM/message_store/";

class DataBase
{
public:
    DataBase() : _database("localhost", "root", "1z2z3z4z5z", "FreeIM") 
    {
        if(_database.connectSQL() == -1) 
        {
            exit(1);
        }
    }
    int registerUser(const string &name, const string &pw);
    int UserLogin(const string &name, const string &pw, const int fd);
    int P2PMessage(const string &from_name, const string &to_name, const string &mes);
    int UserLogout(const int fd);
private:
    SQL _database;
};

#endif
