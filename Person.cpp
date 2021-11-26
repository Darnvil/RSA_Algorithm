#include "Person.h"

const string Person::alphabet = "abcdefghijklmnopqrstuvwxyz ";

inline int gcd(int a, int b)
{
    int c;
    while (b)
    {
        c = a % b;
        a = b;
        b = c;
    }
    return abs(a);
}

void Person::GenKeys()
{
    m = p * q;
    phi = (p - 1) * (q - 1);
    e = FindE();

    openedKey.first = e;
    openedKey.second = m;

    d = FindD();

    closedKey.first = d;
    closedKey.second = m;
}

string Person::GetInfo()
{
    string info;

    info = name + "'s p = " + std::to_string(p) + ", q = " + std::to_string(q) + "\n";
    info += "m = " + std::to_string(m) + ", phi = " + std::to_string(phi) + "\n";
    info += "e = " + std::to_string(e) + ", d = " + std::to_string(d) + "\n";

    info += "opened key is " + openedKey.ToString() + ", closed key is " + closedKey.ToString() + "\n";
    info += "message is " + message + ", encrypted message is ";
    for (auto&& number : encryptedMessage)
        info += std::to_string(number) + " ";
    info += "\n";

    return info;
}

unsigned int Person::FindE()
{
    for (int i = 3; i < phi; ++i)
    {
        if (vec_eratosphen[i] && gcd(i, phi) == 1)
            return i;
    }
}

unsigned int Person::FindD()
{
    for (int i = 2; i < phi; ++i)
    {
        if ((i * e % phi) == 1)
            return i;
    }
}

void Person::encrypt(string msg, Person& other)
{
    vector<int> temp;
    message = msg;
    unsigned long long encryptedNum;
    auto convertedStr = strToInt(msg);
    auto key = GetOpenKeyFromOther(other);
    for (auto&& number : convertedStr)
    {
        unsigned i = 0;
        encryptedNum = 1;
        while (i < key.first)
        {
            encryptedNum *= number;
            encryptedNum %= key.second;
            ++i;
        }

        temp.push_back(encryptedNum);
    }
    encryptedMessage = temp;
    SetEncryptedMessageToOther(other);
}

void Person::decrypt()
{
    vector<int> decrypted;
    unsigned long long decryptedNum;
    for (auto&& number : encryptedMessage)
    {

        unsigned i = 0;
        decryptedNum = 1;
        while (i < closedKey.first)
        {
            decryptedNum *= number;
            decryptedNum %= closedKey.second;
            ++i;
        }

        decrypted.push_back(decryptedNum);
    }
    message = intToStr(decrypted);
}

vector<int> Person::strToInt(string str)
{
    vector<int> result;
    for (auto&& ch : str)
    {
        result.push_back(alphabet.find(ch));
    }
    return result;
}

string Person::intToStr(vector<int> vec)
{
    string result;
    for (auto&& number : vec)
    {
        result += alphabet[number];
    }
    return result;
}

Key Person::GetOpenKeyFromOther(Person& other)
{
    return other.openedKey;
}

void Person::SetEncryptedMessageToOther(Person& other)
{
    other.encryptedMessage = this->encryptedMessage;
}