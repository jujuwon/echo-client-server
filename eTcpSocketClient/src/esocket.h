#pragma once
#include <iostream>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define MSG_LENGTH  1024

struct Esocket
{
protected:
    Esocket(){};
    virtual ~Esocket(){};

public:
    int sock;
    int portNo;
    sockaddr_in servAddr;
    std::string msg;

public:
    void eError(std::string);
};
