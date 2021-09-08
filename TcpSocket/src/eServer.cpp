#include "stdafx.h"

void usage()
{
    std::cout << "syntax : echo-server <port> [-e[-b]]" << std::endl;
    std::cout << "sample : echo-server 1234 -e -b" << std::endl;
}

void error(const char *msg)
{
    std::perror(msg);
    exit(1);
}

int main(int argc, char** argv)
{
    if(argc < 2) {
        usage();
        exit(1);
    }
    int sock, acceptSock;
    int portNo = atoi(argv[1]);
    struct sockaddr_in servAddr, clntAddr;
    socklen_t clntLen;

    // Create a socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock == 0) {
        error("ERROR : Opening socket");
    }

    // Clear address struct
    memset(&servAddr, 0, sizeof(servAddr));
    // Set IP and Port
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servAddr.sin_port = htons(portNo);

    // Binding socket
    if(bind(sock, (struct sockaddr*) &servAddr, sizeof(servAddr)) == -1) {
        error("ERROR : Binding");
    }

    // Listen
    listen(sock, 5);

    clntLen = sizeof(clntAddr);
    // Accept
    acceptSock = accept(sock, (struct sockaddr *) &clntAddr, &clntLen);
    if(acceptSock < 0) {
        error("ERROR : Accept");
    }

    std::cout << "Connection Success" << inet_ntoa(clntAddr.sin_addr) << std::endl;

    // Send msg
    send(acceptSock, "Hello, world!\n", 13, 0);

    int n;
    char buffer[256];
    memset(buffer, 0, sizeof(buffer));

    n = read(acceptSock, buffer, sizeof(buffer)-1);
    if(n < 0) {
        error("ERROR : Read");
    }else {
        std::cout << "Message : " << buffer << std::endl;
    }

    close(acceptSock);
    close(sock);

    return 0;
}