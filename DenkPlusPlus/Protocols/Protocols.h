#pragma once

#include <iostream>
#include "DataTypes/DataTypes.h"

using namespace std;
using namespace DataTypes;

namespace Protocols {

    class EncryptClass {

    public:
        static string randomString(int len);

        static void encrypt();

        static void getKeys();


        class Data {

        };
    };

    class DecryptClass {
    public:
        static void decrypt(const string &pathToBrick, const string &pathToKey);
    };

}

