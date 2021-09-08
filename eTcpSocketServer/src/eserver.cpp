#include "eserver.h"

void Eserver::eUsage()
{
    std::cout << "syntax : echo-server <port> [-e[-b]]" << std::endl;
    std::cout << "sample : echo-server 1234 -e -b" << std::endl;
}

bool Eserver::eMakeSocket(int portNo)
{
    this->portNo = portNo;
    // Create a socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock < 0) {
        eError("ERROR : Opening socket");
        return false;
    }

    // Clear address struct
    memset(&servAddr, 0, sizeof(servAddr));
    // Set IP and Port
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servAddr.sin_port = htons(this->portNo);

    // Binding socket
    if(bind(sock, (struct sockaddr*) &servAddr, sizeof(servAddr)) < 0) {
        eError("ERROR : Binding");
        return false;
    }

    // Listen
    if(listen(sock, 5) < 0) {
        eError("listen");
        return false;
    }
    return true;
}

void Eserver::eAccept()
{
    clntLen = sizeof(clntAddr);
    // Accept
    clntSock = accept(sock, (struct sockaddr *) &clntAddr, &clntLen);
    if(clntSock < 0) {
        eError("ERROR : Accept");
    }
    // std::cout << "Connection Success" << inet_ntoa(clntAddr.sin_addr) << std::endl;

    // Send msg
    // send(servSock, "Hello, world!\n", 13, 0);
}

void Eserver::eRecv()
{
    memset(buffer, 0, sizeof(buffer));
    int n = read(clntSock, buffer, sizeof(buffer)-1);
    if(n < 0) {
        eError("ERROR : Read");
    }else {
        std::cout << "Message : " << buffer << std::endl;
    }
}

void Eserver::eClose()
{
    close(sock);
    close(clntSock);
}
