/*************************************************************************
	> File Name: FreeIM.cpp
	> Author: 
	> Mail: 
	> Created Time: Wed 24 Jan 2018 06:04:17 PM CST
 ************************************************************************/

#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include "FreeIM_Client.h"
using namespace std;

typedef enum{ Online, Offline } State;
State state = Offline;
int input = 0;
string username;
string pw;
string to_user;
string send_message;

void Offline_Select()
{ 
    while(1)
    {
        cout << "0 --- Exit  ---" << endl;
        cout << "1 --- Login  ---" << endl;
        cout << "2 --- Logon ---" << endl;
        cout << "Select: ";
        cin >> input;
        if(input == 0 || input == 1 || input == 2)
            break;
        cout << "Select error, input again" << endl;
    }
    if(input == 0) exit(0);
    cout << "Input user name: ";
    cin >> username;
    cout << "Input password: ";
    cin >> pw;
}

void Online_Select()
{
    while(1)
    {
        printf("\033[2J");
        printf("\033[3;0H");
        cout << "0 --- Exit   ---" << endl;
        cout << "1 --- Send   ---" << endl;
        cout << "2 --- Radio  ---" << endl;
        cout << "3 --- Logout ---" << endl;
        cout << "Select: ";
        cin >> input;
        if(input == 0 || input == 1 || input == 2 || input == 3)
            break;
        cout << "Select error, input again" << endl;
    }
    if(input == 0) exit(0);
    if(input == 3) return;
    if(input == 1)
    {
        cout << "To: ";
        cin >> to_user;
    }
    cout << "Input your message: " << endl;
    cin >> send_message;
}

int main()
{
    printf("\033[2J");
    printf("\033[1;1H");
    Offline_Select();
    FreeIM IM(1219, "120.24.89.156");
    int ret = IM.clientInit();
    if(ret == -1)
    {
        cout << "Client Init Error!" << endl;
    }
    IM.run();
}
