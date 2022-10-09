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

        static void expelKeys();

        static void expelCrypt();

        static void processData();

        static void writeDataToFile();

        static void writeKeysToFile();
    };

    class DecryptClass {
    public:
        static void decrypt();
    };

}

