#pragma once

#include <iostream>

using namespace std;

namespace DataTypes {

    class DataTypesClass {
    public:
        class ProtocolTypesClass {
        public:
            struct Key {
                string shuffle;
                char letter;
            };
            struct BufferKey {
                string reShuffle;
                string shuffle[2];
            };
        };
    };
}

