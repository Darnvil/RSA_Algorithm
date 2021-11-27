#include <iostream>
#include <string>
#include "RSA_Sim.h"

int main()
{
    std::cout << "Enter a message to encrypt: ";
    std::string message;
    std::getline(cin, message);

    RSA_Sim sim;
    sim.Run(message, 0);
    sim.Log();

    return 0;
}