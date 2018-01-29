/*************************************************************************
	> File Name: DataBase.cpp
	> Author: 
	> Mail: 
	> Created Time: Mon 22 Jan 2018 05:44:01 PM CST
 ************************************************************************/

#include "DataBase.h"
#include "TcpConnection.h"
#include <stdio.h>
#include <string.h>
#include <json/json.h>
#include <unistd.h>
#include <fcntl.h>

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
    
    if(pw.compare(res->_row[1]) == 0)
    {
        if(strcmp(res->_row[2], "0") == 0)
        {
            char tmp[6] = {0};
            string set = "user.is_online=1,online.fd=";
            sprintf(tmp, "%d", fd);
            set += tmp;
            string where = "user.id=online.id AND user.id='";
            where += name; where += "'";
            if(_database.updateSQL("user,online", set, where) == -1) return LOGIN_FAIL;

            string store(message_store);
            store+=name;
            int file = open(store.c_str(), O_RDONLY);
            if(file != -1)
            {
                string str;
                char tmp[128] = {0};
                while(read(file, tmp, 128))
                {
                    str += tmp;
                    bzero(tmp, 128);
                }
                TcpConnection conn(fd);
                conn.send(str);
            }
            return DATABASE_OK;
        }
        else
        {
            //修改，后登陆的会使先登录的强行下线
            return USER_IS_ONLINE;
        }
    }
    else
    {
        return PASSWORD_ERROR;
    } 
}

int DataBase::P2PMessage(const string &from_name, const string &to_name, const string &mes)
{
    string sql = "user.id=online.id AND user.id='";
    sql += to_name; sql += "';";
    if(_database.selectSQL("user,online", "user.is_online,online.fd", sql) == -1) return LOGIN_FAIL;
    _database.recvSQL();
    res_row *res = _database.getResult();
    _database.freeResult();
    if(res->isEmpty())
    {
        return NON_EXISTENT;
    }
    else
    {
        Json::Value val;
        val["type"] = 2;
        val["from_name"] = from_name;
        val["message"] = mes;
        if(strcmp(res->_row[0], "1") == 0)
        {
            int fd = atoi(res->_row[1]);
            TcpConnection conn(fd);
            conn.send(val.toStyledString());
        }
        else
        {
            string store(message_store);
            store += to_name;
            int file = open(store.c_str(), O_WRONLY|O_APPEND|O_CREAT);
            if(file != -1)
            {
                write(file, val.toStyledString().c_str(), 
                        sizeof(val.toStyledString().c_str()));
            }
        }
        return DATABASE_OK;
    }
}

int DataBase::UserLogout(const int fd)
{
    char fd_str[16] = {0};
    sprintf(fd_str, "%d", fd);
    string sql = "user.id=online.id AND online.fd='";
    sql += fd_str;
    sql += "'";
    int ret = _database.updateSQL("user,online", "user.is_online=0,online.fd=-1", sql);
    if(ret == -1) return CLOSE_FAIL;
    return DATABASE_OK;
}
