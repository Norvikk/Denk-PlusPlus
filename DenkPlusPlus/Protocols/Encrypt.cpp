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
#include <algorithm>

using namespace KennyLibraries;
using namespace Protocols;
using namespace DataTypes;
using namespace ProcessData;
using namespace std;


list<DataTypesClass::ProtocolTypesClass::Key> ProcessData::ext_keys;
list<DataTypesClass::ProtocolTypesClass::Key>::iterator iteratorKeys;
list<string> ProcessData::ext_processedData;


void EncryptClass::encrypt() {
    auto start = chrono::high_resolution_clock::now();

    Protocols::EncryptClass::getKeys();
    Protocols::EncryptClass::processData();
    Protocols::EncryptClass::writeDataToFile();
    Protocols::EncryptClass::writeKeysToFile();
    Protocols::EncryptClass::expelDecrypted();
    if (ext_isDebugging){
        Protocols::EncryptClass::expelKeys();
        Protocols::EncryptClass::expelCrypt();
        Protocols::EncryptClass::expelDecrypted();
    }

    auto finish = std::chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = (finish - start) * 1000;
    cout << endl << ProcessData::ext_iterationData << " Iterations" << endl << ext_messageData.size() << " chars" << endl;
    cout << "Rounded Elapsed Time: " << round(elapsed.count())  << " ms"  << endl << "Full Elapsed Time: " << elapsed.count() << " ms" <<endl <<endl;
}

void EncryptClass::getKeys() {
    list<char> used; DataTypesClass::ProtocolTypesClass::Key temporary;
    for (char c: ext_messageData) {
        if(!(find(used.begin(), used.end(), c) != used.end())){
            temporary.letter = c;
            temporary.shuffle = KennyLibraries::Get::randomString(ext_iterationData);
            ext_keys.push_back(temporary);
            used.push_back(c);  }
    }
}

void EncryptClass::expelKeys() {
    for (iteratorKeys = ext_keys.begin(); iteratorKeys != ext_keys.end(); iteratorKeys++) {
        cout << iteratorKeys->letter << "||" << iteratorKeys->shuffle << endl;
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
        for (iteratorKeys = ext_keys.begin(); iteratorKeys != ext_keys.end(); iteratorKeys++) {
            if (iteratorKeys->letter == c)
                ext_processedData.push_back(iteratorKeys->shuffle);
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
    for (iteratorKeys = ext_keys.begin(); iteratorKeys != ext_keys.end(); iteratorKeys++) {MyFile << iteratorKeys->letter << " " << iteratorKeys->shuffle << " " << endl;}
    MyFile.close();
}

void EncryptClass::expelDecrypted() {
    for (string const &s: ext_processedData) {
        for (iteratorKeys = ext_keys.begin(); iteratorKeys != ext_keys.end(); iteratorKeys++) {
            if (iteratorKeys->shuffle == s) { cout << iteratorKeys->letter; }
        }
    }
}
