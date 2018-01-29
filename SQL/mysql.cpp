/*************************************************************************
	> File Name: mysql.cpp
	> Author: 
	> Mail: 
	> Created Time: Mon 22 Jan 2018 03:01:01 PM CST
 ************************************************************************/

#include <iostream>
using namespace std;
#include "SQL.h"

int main()
{
    SQL mysql("localhost", "root", "1z2z3z4z5z");
    mysql.connectSQL();
    mysql.useDatabase("FreeIM");
    mysql.insertSQL("user", "'test',123,0");
    mysql.selectSQL("user");
    mysql.recvSQL();
    res_row *row = NULL;
    do{
        row = mysql.getResult();
        if(row != NULL && !row->isEmpty())
        {
            int fields = row->_fields;
            int i = 0;
            for(; i < fields; ++i)
            {
                cout << (row->_row)[i] << "  ";
            }
            cout << endl;
        }
    }while(!row->isEmpty());
    mysql.freeResult();

    cout << endl;
    mysql.deleteSQL("user", "id", "'test'");
    mysql.updateSQL("online", "fd=20", "id='zhangyu'");

    mysql.selectSQL("online");
    mysql.recvSQL();
    row = NULL;
    do{
        row = mysql.getResult();
        if(row != NULL && !row->isEmpty())
        {
            int fields = row->_fields;
            int i = 0;
            for(; i < fields; ++i)
            {
                cout << (row->_row)[i] << "  ";
            }
            cout << endl;
        }
    }while(!row->isEmpty());
    mysql.freeResult();
}
