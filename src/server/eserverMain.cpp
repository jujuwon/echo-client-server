#include "stdafx.h"

int main(int argc, char **argv)
{
    if(argc < 2 || argc > 4) {
        Eserver::eUsage();
        exit(1);
    }

    Eserver server;

    server.optCheck(argc, argv);

    int portNo = atoi(argv[1]);
    server.eMakeSocket(portNo);
    server.eConnect();

    return 0;
}
