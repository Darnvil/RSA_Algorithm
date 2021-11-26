#pragma once
#include <iostream>
#include <string>
#include "Person.h"

using std::cout;
using std::string;

class RSA_Sim
{
    Person alice, bob;

public:
    RSA_Sim() : alice("Alice"), bob("Bob") {}

    void Run(string messageToSend, int from); // from specifies which one will send message: 0 - alice, 1 - bob

    void Log();
};
