#pragma once

#include <iostream>
#include "../DataTypes/DataTypes.h"

using namespace std;
using namespace DataTypes;

namespace Protocols {

    class EncryptClass {

    public:
        static void encrypt();



    private:
        static void expelCrypt();

        static void processData();

        static void writeDataToFile();

        static void expelDecrypted();

        static void bufferData();

        static void decentralize();
    };

    class DecryptClass {
    public:
        static void decrypt();



    private:
        static void readBricked();
        static void readKeys();
        static void centralize();
        static void output();


    };

}

