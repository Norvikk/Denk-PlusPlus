#include "Protocols.h"
#include "DataTypes/DataTypes.h"
#include "DataTypes/UniversalData.h"
#include <iostream>
#include "list"


using namespace Protocols;
using namespace DataTypes;
using namespace std;


string EncryptClass::randomString(const int len) {
    static const char alphanum[] =
            "0123456789"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz"
            "!§$%&/()=?'*_-.-<>|~²³{[]}";
    string tmp_s;
    tmp_s.reserve(len);

    for (int i = 0; i < len; ++i) {
        tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];
    }

    return tmp_s;
}


void EncryptClass::encrypt() {
    Protocols::EncryptClass::getKeys();
    cout << Keys.size();
}

list<DataTypesClass::ProtocolTypesClass::Key> Keys;
void EncryptClass::getKeys() {
    list<DataTypesClass::ProtocolTypesClass::Key>::iterator carrier;




    for (char c: ext_messageData) {
        cout << "I ran " << c << endl;

        bool requiresCreation = true;

        for (carrier = Keys.begin(); carrier != Keys.end(); carrier++) {
            if (carrier->letter == c) {
                requiresCreation = false;
                cout << "Letter already exists" << endl;
                break;
            }
        }

        if (requiresCreation) {
            DataTypesClass::ProtocolTypesClass::Key temporary;
            temporary.letter = c;
            temporary.shuffle = randomString(ext_iterationData);
            Keys.push_back(temporary);
            cout << "new letter " << c << " has been created" << endl;
            cout << "new shuffle " << temporary.shuffle << " has been created" << endl;
        }

    }
}

