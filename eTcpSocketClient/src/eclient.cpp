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

void Eclient::eSendRecv()
{
    pthread_create(&sendThread, NULL, eSend, (void*)&sock);
    pthread_create(&recvThread, NULL, eRecv, (void*)&sock);
    pthread_detach(sendThread);
    pthread_join(recvThread, NULL);
    close(sock);
}

void *Eclient::eSend(void *arg)
{
    int sock = *((int*)arg);
    char sendMsg[MSG_LENGTH];

    while(true) {
        memset(sendMsg, 0, sizeof(sendMsg));
        std::cin.getline(sendMsg, MSG_LENGTH);
        write(sock, sendMsg, strlen(sendMsg));
    }

    return NULL;
}

void *Eclient::eRecv(void *arg)
{
    int sock = *((int*)arg);
    char recvMsg[MSG_LENGTH];
    int length;

    while(true) {
        length = read(sock, recvMsg, sizeof(recvMsg));
        if(length == -1) {
            std::cout << "ERROR : Recv" << std::endl;
            exit(1);
        }
        std::cout << "Message : " << recvMsg << std::endl;
    }
    return NULL;
}


void Eclient::eClose()
{
    close(sock);
}
