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
    while(true) {
        try {
            client.eSend();
        }  catch (...) {
            client.eClose();
            exit(1);
        }
    }

    client.eClose();
    return 0;
}
