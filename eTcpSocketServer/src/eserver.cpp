#include "eserver.h"

int Eserver::clntCnt = 0;
int Eserver::clntSocks[];
bool Eserver::echo = false;
bool Eserver::broad = false;

void Eserver::eUsage()
{
    std::cout << "syntax : echo-server <port> [-e[-b]]" << std::endl;
    std::cout << "sample : echo-server 1234 -e -b" << std::endl;
}

void Eserver::eMakeSocket(int portNo)
{
    this->portNo = portNo;
    // Create a socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock < 0) {
        eError("ERROR : Opening socket");
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
    }

    // Listen
    if(listen(sock, 5) < 0) {
        eError("listen");
    }

    pthread_mutex_init(&mutx, NULL);
}

void Eserver::eConnect()
{
    while(true) {
        clntLen = sizeof(clntAddr);
        // Accept
        clntSock = accept(sock, (struct sockaddr *) &clntAddr, &clntLen);
        if(clntSocks[clntCnt] < 0) {
            eError("ERROR : Accept");
        }

        pthread_mutex_lock(&mutx);
        clntSocks[clntCnt] = clntSock;
        pthread_mutex_unlock(&mutx);

        pthread_create(&id[clntCnt], NULL, eSendRecv, (void*)&clntSock);
        pthread_detach(id[clntCnt++]);

        std::cout << "Connection Success : " << inet_ntoa(clntAddr.sin_addr) << std::endl;
    }
    eClose(clntSock);
}

void *Eserver::eSendRecv(void *arg)
{
    int clntSock = *((int*)arg);
    int length = 0;
    char msg[1024];

    while((length = read(clntSock, msg, sizeof(msg)-1)) != 0) {
        if(echo) {
            if(broad) {
                for(int i=0; i<clntCnt; i++) {
                    write(clntSocks[i], msg, sizeof(msg));
                }
            }else {
                write(clntSock, msg, sizeof(msg));
            }
        }

        std::cout << "Message : " << msg << std::endl;
        memset(msg, 0, sizeof(msg));
    }

    return NULL;
}

void Eserver::eClose(int clntSock)
{
    close(sock);
    close(clntSock);
}

void Eserver::optCheck(int argc, char ** argv)
{
    for(int i=0; i<argc; i++) {
        if(!strcmp((argv[i]), "-e")) echo = true;
        if(!strcmp((argv[i]), "-b")) broad = true;
    }
}
