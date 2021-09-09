#include "stdafx.h"

int main(int argc, char** argv)
{
    Eclient client;

    if(argc < 3) {
        Eclient::eUsage();
        exit(1);
    }

    char *addr = argv[1];
    int portNo = atoi(argv[2]);
    client.eMakeSocket(addr, portNo);
    client.eSendRecv();
    client.eClose();
    return 0;
}
