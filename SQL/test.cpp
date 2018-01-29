/*************************************************************************
	> File Name: test.cpp
	> Author: 
	> Mail: 
	> Created Time: Sun 21 Jan 2018 12:39:10 PM CST
 ************************************************************************/

#include <iostream>
#include <mysql/mysql.h>
using namespace std;

int main()
{
    MYSQL *connection = mysql_init(NULL);
    MYSQL_RES *result;
    MYSQL_ROW row;

    connection = mysql_real_connect(connection, "localhost", "root", "1z2z3z4z5z", "mysql", 0, NULL, 0);
    mysql_query(connection, "SELECT * FROM user WHERE user='root';");
    for(int i=0; i < mysql_field_count(connection); ++i)  
    {
        row = mysql_fetch_row(result);  
        if(row <= 0)  
        {
            break;
        }
        for(int j=0; j < mysql_num_fields(result); ++j)  
        {  
            cout << row[j] << " ";  
        }  
        cout << endl;  
    }
    mysql_free_result(result);

    mysql_close(connection);
    return 0;
}
