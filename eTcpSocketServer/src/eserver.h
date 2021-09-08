#pragma once
#include "esocket.h"

class Eserver : Esocket
{
public:
    Eserver(){};
    ~Eserver(){};

protected:
    sockaddr_in clntAddr;
    socklen_t clntLen;
    int clntSock;

public:
    static void eUsage();
    bool eMakeSocket(int portNo);
    void eAccept();
    void eRecv();
    void eClose();
};
