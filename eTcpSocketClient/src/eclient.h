#pragma once
#include "esocket.h"

struct Eclient : Esocket
{
    Eclient(){};
    ~Eclient(){};
    char buffer[MSG_LENGTH];

public:
    static void eUsage();
    bool eMakeSocket(char* addr, int portNo);
    bool eSend();
    void eClose();
};
