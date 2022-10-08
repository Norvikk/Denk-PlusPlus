#include <iostream>
#include "Protocols/DataTypes/DataTypes.h"

using namespace std;
using namespace DataTypes;

namespace Playground {
    static void MainPlayground() {
        cout << "Main playground area" << endl;

        DataTypes::DataTypesClass::Student Hex;
        Hex.age = 69420;
        Hex.born[1] = 18;
        Hex.born[2] = 3;
        Hex.born[3] = 1954;

        Hex.creditCard = 494320891;
        Hex.hairAmount = 466593655454542;

        Hex.firstName = "HexO";
        Hex.lastName = "fDoom";

        Hex.height = 184.4;
        Hex.width = 350.1;


        cout << Hex.age << Hex.born[1] << Hex.born[2] << Hex.born[3] << Hex.creditCard << Hex.hairAmount
             << Hex.firstName << Hex.lastName << Hex.width << Hex.height << endl;
    }

}

