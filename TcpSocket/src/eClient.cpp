#include "stdafx.h"

void usage()
{
    std::cout << "echo-client:" << std::endl;
    std::cout << "syntax : echo-client <ip> <port>" << std::endl;
    std::cout << "sample : echo-client 192.168.10.2 1234" << std::endl;
}

void error(const char *msg)
{
    std::perror(msg);
    exit(1);
}

int main(int argc, char ** argv)
{
    if(argc < 3) {
        usage();
        exit(1);
    }

    int sock, portNo = atoi(argv[2]);
    struct sockaddr_in servAddr;

    // Create a socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock < 0) {
        error("ERROR : Socket");
    }

    // Clear address struct
    memset(&servAddr, 0, sizeof(servAddr));
    // Set IP and Port
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = inet_addr(argv[1]);
    servAddr.sin_port = htons(portNo);

    // Connect Server
    if(connect(sock, (struct sockaddr *) &servAddr, sizeof(servAddr)) < 0) {
        error("ERROR : Connect");
    }

    std::cout << "Enter msg : " << std::endl;
    
    int n;
    char buffer[256];
    memset(buffer, 0, sizeof(buffer));
    std::cin.getline(buffer, 255);
    n = write(sock, buffer, strlen(buffer));
    if(n < 0) {
        error("ERROR : Write");
    }

    close(sock);
    return 0;
}