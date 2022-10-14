#include "Protocols.h"
#include "../DataTypes/DataTypes.h"
#include "../DataTypes/UniversalData.h"
#include "../Kenny//KennyPlusPlus.h"
#include <iostream>
#include "list"
#include <chrono>
#include <fstream>
#include <string>
#include <cmath>

using namespace KennyLibraries;
using namespace Protocols;
using namespace DataTypes;
using namespace ProcessData;
using namespace std;


list<DataTypesClass::ProtocolTypesClass::Key> ProcessData::ext_keys;
list<DataTypesClass::ProtocolTypesClass::Key>::iterator carrier;
list<string> ProcessData::ext_processedData;


void EncryptClass::encrypt() {
    auto start = chrono::high_resolution_clock::now();

    Protocols::EncryptClass::getKeys();
    Protocols::EncryptClass::processData();
    Protocols::EncryptClass::writeDataToFile();
    Protocols::EncryptClass::writeKeysToFile();
    if (ext_isDebugging){
        Protocols::EncryptClass::expelKeys();
        Protocols::EncryptClass::expelCrypt();
        Protocols::EncryptClass::expelDecrypted();
    }

    chrono::duration<double> elapsed = (chrono::high_resolution_clock::now() - start) * 1000;
    cout << endl << "Rounded Elapsed Time: " << round(elapsed.count())  << " ms"  << endl << "Full Elapsed Time: " << elapsed.count() << " ms" <<endl <<endl;
}

void EncryptClass::getKeys() {
    bool requiresCreation;
    for (char c: ext_messageData) {
        if (ext_isDebugging) cout << "I ran " << c << endl;
        requiresCreation = true;

        for (carrier = ext_keys.begin(); carrier != ext_keys.end(); carrier++) {
            if (carrier->letter == c) {
                requiresCreation = false;
                if (ext_isDebugging) cout << "Letter already exists" << endl;
                break;
            }
        }

        if (requiresCreation) {
            DataTypesClass::ProtocolTypesClass::Key temporary;
            temporary.letter = c;
            temporary.shuffle = KennyLibraries::Get::randomString(ext_iterationData);
            for (carrier = ext_keys.begin(); carrier != ext_keys.end(); carrier++) {
                if (carrier->shuffle == temporary.shuffle) temporary.shuffle = KennyLibraries::Get::randomString(ext_iterationData);
            }
            ext_keys.push_back(temporary);
            if (ext_isDebugging) cout << "new letter " << c << " has been created" << endl;
            if (ext_isDebugging) cout << "new shuffle " << temporary.shuffle << " has been created" << endl;
        }
    }
}

void EncryptClass::expelKeys() {
    for (carrier = ext_keys.begin(); carrier != ext_keys.end(); carrier++) {
        cout << carrier->letter << "||" << carrier->shuffle << endl;
    }
}

void EncryptClass::expelCrypt() {
    if (ext_isDebugging) cout << ext_processedData.size() << endl;
    for (auto const &i: ext_processedData) {
        std::cout << i << std::endl;
    }
}

void EncryptClass::processData() {
    if (ext_isDebugging) cout << "size of message " << ext_messageData.size() << endl;
    for (char c: ext_messageData) {
        for (carrier = ext_keys.begin(); carrier != ext_keys.end(); carrier++) {
            if (carrier->letter == c)
                ext_processedData.push_back(carrier->shuffle);
        }
    }
}

void EncryptClass::writeDataToFile() {
    ofstream TestFile("../DenkPlusPlus/Output/Output.txt");
    for (string const &s: ext_processedData) {TestFile << s;}
    TestFile.close();
}

void EncryptClass::writeKeysToFile() {
    ofstream MyFile("../DenkPlusPlus/Output/Keys.txt");
    for (carrier = ext_keys.begin(); carrier != ext_keys.end(); carrier++) {MyFile << carrier->letter << " " << carrier->shuffle << " " << endl;}
    MyFile.close();
}

void EncryptClass::expelDecrypted() {
    for (string const &s: ext_processedData) {
        for (carrier = ext_keys.begin(); carrier != ext_keys.end(); carrier++) {
            if (carrier->shuffle == s) { cout << carrier->letter; }
        }
    }
}
