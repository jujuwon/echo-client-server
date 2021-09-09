#pragma once
#include <iostream>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>

#define MSG_LENGTH  1024

class Esocket
{
protected:
    Esocket(){};
    virtual ~Esocket(){};

protected:
    int sock;
    int portNo;
    sockaddr_in servAddr;
    std::string msg;
    char buffer[MSG_LENGTH];

public:
    void eError(std::string msg);
};
