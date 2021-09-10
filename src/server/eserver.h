#pragma once
#include "esocket.h"
#include <string.h>

#define MAX_CLNT    100

class Eserver : Esocket
{
public:
    Eserver(){};
    ~Eserver(){};


protected:
    sockaddr_in clntAddr;
    socklen_t clntLen;
    int clntSock;
    static int clntSocks[MAX_CLNT];
    static int clntCnt;
    static bool echo;
    static bool broad;
    pthread_mutex_t mutx;
    pthread_t id[MAX_CLNT];

public:
    static void eUsage();
    void eMakeSocket(int portNo);
    void eConnect();
    static void *eSendRecv(void *arg);
    void eClose(int clntSock);
    void optCheck(int argc, char ** argv);
};
