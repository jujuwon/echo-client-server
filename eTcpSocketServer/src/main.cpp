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
    server.eAccept();
    while(true) {
        try {
            server.eRecv();
        }  catch (...) {
            server.eClose();
            exit(1);
        }
    }

    server.eClose();
    return 0;
}
