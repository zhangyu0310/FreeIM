/*************************************************************************
	> File Name: string_test.cpp
	> Author: 
	> Mail: 
	> Created Time: Thu 25 Jan 2018 09:27:10 PM CST
 ************************************************************************/

#include <iostream>
#include <string>
#include <stdio.h>
using namespace std;

int main()
{
    int fd = 51;
    char tmp[6] = {0};
    sprintf(tmp, "%d", fd);
    string sql = "user.is_online=1,online.fd=";
    sql += tmp;
    cout << sql << endl;
}
