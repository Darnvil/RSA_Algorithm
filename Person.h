#pragma once
#include <utility>
#include <vector>
#include <random>
#include <string>
#include "Eratosphen.h"

using std::string;
using std::vector;

struct Key
{
    unsigned int first, second;

    string ToString() { return "{ " + std::to_string(first) + " " + std::to_string(second) + " }"; }
};

class Person
{
public:
    Person(string _name) : name(std::move(_name)), eng(rd()), distr(10, 100)
    {

        int size = 600000;
        vec_eratosphen = Eratosphen(size);
        int i = distr(eng);
        while (!vec_eratosphen[i])
            i = distr(eng);
        p = i;
        i = distr(eng);
        while (!vec_eratosphen[i])
            i = distr(eng);
        q = i;
    }

    string GetInfo();

    void GenKeys();

    void encrypt(string msg, Person& other);
    void decrypt();

    Key GetOpenKeyFromOther(Person& other);
    void SetEncryptedMessageToOther(Person& other);

    Key openedKey;

private:
    const string name;
    std::random_device rd;
    std::default_random_engine eng;
    std::uniform_int_distribution<int> distr;
    unsigned int p, q, m, phi, e, d;
    Key closedKey;
    vector<bool> vec_eratosphen;
    string message;
    vector<int> encryptedMessage;

    static const string alphabet;

    unsigned int FindE();
    unsigned int FindD();

    vector<int> strToInt(string str);
    string intToStr(vector<int> vec);
};