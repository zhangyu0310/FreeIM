/*************************************************************************
	> File Name: DataBase.cpp
	> Author: 
	> Mail: 
	> Created Time: Mon 22 Jan 2018 05:44:01 PM CST
 ************************************************************************/

#include "DataBase.h"
#include <stdio.h>
#include <string.h>
#include <iostream>
using std::cout; using std::endl;

int DataBase::registerUser(const string &name, const string &pw)
{
    string sql = "'"; sql += name; sql += "',"; sql += "'";
    sql += pw; sql += "',0";
    if(_database.insertSQL("user", sql) == -1) return REGISTER_FAIL;

    return DATABASE_OK;
}

int DataBase::UserLogin(const string &name, const string &pw, const int fd)
{
    string sql = "id='"; sql += name; sql +="'";
    if(_database.selectSQL("user", "*", sql) == -1) return LOGIN_FAIL;
    _database.recvSQL();
    res_row *res = _database.getResult();
    _database.freeResult();
    if(res->isEmpty())
    {
        return NON_EXISTENT;
    }
    if(name.compare(res->_row[0]) == 0)
    {
        if(pw.compare(res->_row[1]) == 0)
        {
            if(strcmp(res->_row[2], 0) == 0)
            {
                char tmp[6] = {0};
                string set = "user.is_online=1,online.fd=";
                sprintf(tmp, "%d", fd);
                set += tmp;
                string where = "user.id=online.id AND user.id='";
                where += name; where += "'";
                if(_database.updateSQL("user,online", set, where) == -1) return LOGIN_FAIL;
                return DATABASE_OK;
            }
            else
            {
                return USER_IS_ONLINE;
            }
        }
        else
        {
            return PASSWORD_ERROR;
        }
    }
    else
    {
        return NAME_ERROR;
    }
}
