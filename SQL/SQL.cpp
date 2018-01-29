/*************************************************************************
	> File Name: SQL.cpp
	> Author: 
	> Mail: 
	> Created Time: Mon 22 Jan 2018 01:45:44 PM CST
 ************************************************************************/
//#include <iostream>
//using std::cout; using std::endl;
#include "SQL.h"

int SQL::connectSQL()
{
    const char *db = NULL;
    const char *us = NULL;
    if(_db.compare("") != 0)
    { db = _db.c_str(); }
    if(_unix_socket.compare("") != 0)
    { us = _unix_socket.c_str(); }

    _mysql = mysql_real_connect(_mysql, _host.c_str(), _user.c_str(), _pw.c_str(), db, _port, us, _flag);
    if(_mysql == NULL) return -1;
    return 0;
}

int SQL::insertSQL(const string &table, const string &values, const string &columns)
{
    if(!isConnected()) return -1;

    string sql = "INSERT INTO "; sql += table;
    if(columns.compare("") != 0)
    {
        sql += " ("; sql += columns; sql += ") ";
    }
    sql += " VALUES ("; sql += values; sql += ");";

    //cout << sql << endl;
    
    if(mysql_query(_mysql, sql.c_str()))
    { return -1; }

    return 0;
}

int SQL::deleteSQL(const string &table, const string &column, const string &key)
{
    if(!isConnected()) return -1;

    string sql = "DELETE FROM "; sql += table; sql += " WHERE ";
    sql += column; sql += " = "; sql += key; sql += ";";

    //cout << sql << endl;
    
    if(mysql_query(_mysql, sql.c_str())) 
    { return -1; }

    return 0;
}

int SQL::updateSQL(const string &table, const string &set, const string &where)
{
    if(!isConnected()) return -1;

    string sql = "UPDATE "; sql += table; sql += " SET ";
    sql += set; sql += " WHERE "; sql += where; sql += ";";
    
    //cout << sql << endl;
    
    if(mysql_query(_mysql, sql.c_str())) 
    { return -1; }

    return 0;
}

int SQL::selectSQL(const string &tables, const string &columns, const string &where)
{
    if(!isConnected()) return -1;
    //为容易识别，故横向排列
    string sql = "SELECT ";  sql += columns;  sql += " FROM ";  sql += tables;
    if(where.compare("") != 0)
    { sql += " WHERE ";  sql += where; }
    sql += ";";

    //cout << sql << endl;
    
    if(mysql_query(_mysql, sql.c_str())) 
    { return -1; }

    return 0;
}
