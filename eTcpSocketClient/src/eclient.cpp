#include "eclient.h"

void Eclient::eUsage()
{
    std::cout << "syntax : echo-client <ip> <port>" << std::endl;
    std::cout << "sample : echo-client 192.168.10.2 1234" << std::endl;
}

bool Eclient::eMakeSocket(char *addr, int portNo)
{
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock < 0) {
        eError("Socket Error!");
        return false;
    }

    // Set Address
    memset(&servAddr, 0, sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = inet_addr(addr);
    servAddr.sin_port = htons(portNo);

    // Connect
    if(connect(sock, (struct sockaddr *) &servAddr, sizeof(servAddr)) < 0) {
        eError("Connect Error");
        return false;
    }
    return true;
}

bool Eclient::eSend()
{
    int n;
    memset(buffer, 0, sizeof(buffer));
    std::cin.getline(buffer, MSG_LENGTH);
    n = write(sock, buffer, strlen(buffer));
    if(n < 0) {
        eError("Write");
        return false;
    }

    return true;
}

void Eclient::eClose()
{
    close(sock);
}
