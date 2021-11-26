#include "RSA_Sim.h"

void RSA_Sim::Run(string messageToSend, int from) // from specifies which one will send message: 0 - alice, 1 - bob
{
    alice.GenKeys();
    bob.GenKeys();

    Person& sender = from ? bob : alice;
    Person& client = from ? alice : bob;

    sender.encrypt(messageToSend, client);
    client.decrypt();
}

void RSA_Sim::Log()
{
    std::cout << alice.GetInfo();

    std::cout << bob.GetInfo();
}