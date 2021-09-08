#include "esocket.h"

void Esocket::eError(std::string msg)
{
    std::cout << msg << std::endl;
    exit(1);
}
