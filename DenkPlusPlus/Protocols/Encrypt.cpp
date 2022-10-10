#include "Protocols.h"
#include "../DataTypes/DataTypes.h"
#include "../DataTypes/UniversalData.h"
#include <iostream>
#include "list"
#include <chrono>
#include <fstream>

using namespace Protocols;
using namespace DataTypes;
using namespace ProcessData;
using namespace std;

list<DataTypesClass::ProtocolTypesClass::Key> ProcessData::ext_keys;
list<DataTypesClass::ProtocolTypesClass::Key>::iterator carrier;

list<string> ProcessData::ext_processedData;

bool isDebugging;

string EncryptClass::randomString(const int len) {
    static const char alphanum[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    string tmp_s;
    for (int i = 0; i < len; ++i) { tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)]; }
    return tmp_s;
}

void temporalDecryption() {
    for (string const &s: ext_processedData) {
        for (carrier = ext_keys.begin(); carrier != ext_keys.end(); carrier++) {
            if (carrier->shuffle == s) { cout << carrier->letter; }
        }
    }
}


void EncryptClass::encrypt() {
    auto start = chrono::high_resolution_clock::now();
    Protocols::EncryptClass::getKeys();
    //Protocols::EncryptClass::expelKeys();
    Protocols::EncryptClass::processData();
    //Protocols::EncryptClass::expelCrypt();
    Protocols::EncryptClass::writeDataToFile();
    Protocols::EncryptClass::writeKeysToFile();
    temporalDecryption();
    auto finish = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = (finish - start) * 1000;
    cout << endl << "Elapsed Time: " << elapsed.count() << " ms\n";
}

void EncryptClass::getKeys() {
    bool requiresCreation;
    for (char c: ext_messageData) {
        if (isDebugging) cout << "I ran " << c << endl;

        requiresCreation = true;

        for (carrier = ext_keys.begin(); carrier != ext_keys.end(); carrier++) {
            if (carrier->letter == c) {
                requiresCreation = false;
                if (isDebugging) cout << "Letter already exists" << endl;
                break;
            }
        }

        if (requiresCreation) {
            DataTypesClass::ProtocolTypesClass::Key temporary;
            temporary.letter = c;
            temporary.shuffle = randomString(ext_iterationData);
            for (carrier = ext_keys.begin(); carrier != ext_keys.end(); carrier++) {
                if (carrier->shuffle == temporary.shuffle) temporary.shuffle = randomString(ext_iterationData);
            }
            ext_keys.push_back(temporary);
            if (isDebugging) cout << "new letter " << c << " has been created" << endl;
            if (isDebugging) cout << "new shuffle " << temporary.shuffle << " has been created" << endl;
        }
    }
}

void EncryptClass::expelKeys() {
    for (carrier = ext_keys.begin(); carrier != ext_keys.end(); carrier++) {
        cout << carrier->letter << "||" << carrier->shuffle << endl;
    }
}

void EncryptClass::expelCrypt() {
    if (isDebugging) cout << ext_processedData.size() << endl;
    for (auto const &i: ext_processedData) {
        std::cout << i << std::endl;
    }
}

void EncryptClass::processData() {
    if (isDebugging) cout << "size of message " << ext_messageData.size() << endl;
    for (char c: ext_messageData) {
        for (carrier = ext_keys.begin(); carrier != ext_keys.end(); carrier++) {
            if (carrier->letter == c)
                ext_processedData.push_back(carrier->shuffle);
        }
    }
}

void EncryptClass::writeDataToFile() {
    ofstream MyFile("../Output/output.txt");
    for (string const &s: ext_processedData) {
        MyFile << s;
    }
    MyFile.close();
}

void EncryptClass::writeKeysToFile() {
    ofstream MyFile("../Output/keys.txt");
    for (carrier = ext_keys.begin(); carrier != ext_keys.end(); carrier++) {
        MyFile << carrier->letter << " " << carrier->shuffle << " " << endl;
    }
    MyFile.close();
}

