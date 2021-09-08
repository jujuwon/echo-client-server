#include "stdafx.h"

int main(int argc, char **argv)
{
    if(argc < 2) {
        Eserver::eUsage();
        exit(1);
    }

    Eserver server;
    int portNo = atoi(argv[1]);
    server.eMakeSocket(portNo);
    while(true) {
        server.eAccept();
    }

    return 0;
}
