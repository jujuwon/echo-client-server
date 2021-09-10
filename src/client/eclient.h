#pragma once
#include "esocket.h"

struct Eclient : Esocket
{
    Eclient(){};
    ~Eclient(){};
    pthread_mutex_t mutx;
    pthread_t sendThread, recvThread;

public:
    static void eUsage();
    bool eMakeSocket(char* addr, int portNo);
    void eSendRecv();
    static void *eSend(void *arg);
    static void *eRecv(void *arg);
    void eClose();
};
