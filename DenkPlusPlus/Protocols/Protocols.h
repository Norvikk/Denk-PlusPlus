#pragma once
#include <iostream>
using namespace std;

namespace Protocols {

    class EncryptClass{
    public:
        static void encrypt(const string& message, int iterations);
    };

    class DecryptClass{
    public:
        static void decrypt(const string& pathToBrick, const string& pathToKey);
    };

}

