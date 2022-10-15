#pragma once

#include <iostream>
#include "../DataTypes/DataTypes.h"

using namespace std;
using namespace DataTypes;

namespace Protocols {

    class EncryptClass {

    public:
        static void encrypt();

        static void expelCrypt();

        static void processData();

        static void writeDataToFile();

        static void expelDecrypted();
    };

    class DecryptClass {
    public:
        static void decrypt();
    };

}

