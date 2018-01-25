/*************************************************************************
	> File Name: SQL.h
	> Author: 
	> Mail: 
	> Created Time: Mon 22 Jan 2018 12:55:24 PM CST
 ************************************************************************/

#ifndef _SQL_H
#define _SQL_H

#include <string>
#include <mysql/mysql.h>
using std::string;

struct res_row
{
    unsigned int _fields;
    MYSQL_ROW _row;

    bool isEmpty() { return _row == NULL; }
};

class SQL
{
public:
    SQL(const string &host, const string &user, const string &pw, 
        const string &db = "", const unsigned int port = 3306, 
        const string &unix_socket = "", const unsigned long flag = 0) :
                                        _host(host), _user(user), _pw(pw), _db(db),
                                        _port(port), _unix_socket(unix_socket), _flag(flag)
    {
        _mysql = mysql_init(NULL);
    }

    int connectSQL();

    bool isConnected() { return _mysql != NULL; }

    int useDatabase(const string &db)
    {
        _db = db;
        if(!isConnected()) return -1;

        if(mysql_select_db(_mysql, _db.c_str()))
        {
            return -1;
        }
        return 0;
    }

    //int createTable(const string &table_name);
    //int dropTable();
    //int dropDatabase();
    int truncateTable(const string &table)
    {
        string sql = "TRUNCATE "; sql += table; sql += ";";
        if(mysql_query(_mysql, sql.c_str()))
        { return -1; }

        return 0;
    }

    int insertSQL(const string &table, const string &values, const string &columns = "");
    int deleteSQL(const string &table, const string &column, const string &key);
    int updateSQL(const string &table, const string &set, const string &where);
    int selectSQL(const string &tables, const string &columns = "*", const string &where = "");

    void recvSQL() 
    {
        if(!isConnected()) return;

        _res = mysql_store_result(_mysql); 
    }

    res_row* getResult()
    {
        if(_res == NULL)
        {
            _row._fields = 0;
            _row._row = NULL;

            return &_row;
        }

        _row._fields = mysql_num_fields(_res);
        _row._row = mysql_fetch_row(_res);
        return &_row;
    }

    void freeResult()
    {
        if(_res == NULL) return;

        mysql_free_result(_res);
        //cout << "Result is free" << endl;
    }

    void closeSQL() 
    {
        if(!isConnected()) return;

        mysql_close(_mysql); 
        _mysql = NULL; 
    }
private:
    MYSQL *_mysql;
    MYSQL_RES *_res;
    //MYSQL_ROW _row;
    struct res_row _row;
    string _host;
    string _user;
    string _pw;
    string _db;
    unsigned int _port;
    string _unix_socket;
    unsigned long _flag;
};

#endif
