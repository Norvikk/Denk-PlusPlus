#pragma once

#include <iostream>

using namespace std;

namespace DataTypes {

    class DataTypesClass {
    public:
        struct Student {
            string firstName;
            string lastName;

            int age;
            int born[3];

            double height;
            double width;

            long creditCard;
            long long hairAmount;
        };

        class ProtocolTypesClass {
        public:
            struct Key {
                string shuffle;
                char letter;
            };
        };
    };
}

