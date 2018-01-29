/*************************************************************************
	> File Name: State_Offline.h
	> Author: 
	> Mail: 
	> Created Time: Wed 24 Jan 2018 06:36:48 PM CST
 ************************************************************************/

#ifndef _STATE_OFFLINE_H
#define _STATE_OFFLINE_H
#include "State.h"

class TcpConnection;
class Offline : public State
{
public:
    void doAction(Context &context);
    void sendRequest(TcpConnection *conn);
    int recvResponse(TcpConnection *conn);
private:
    int _input;
};
#endif
