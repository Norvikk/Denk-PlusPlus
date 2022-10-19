#include "../DataTypes/DataTypes.h"
#include "../DataTypes/UniversalData.h"
#include "../Kenny//KennyPlusPlus.h"
#include "list"
#include "Protocols.h"
#include <iostream>
#include <chrono>
#include <fstream>
#include <string>
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include "cmath"

using namespace std;
using namespace KennyLibraries;

using namespace Protocols;
using namespace DataTypes;
using namespace ProcessData;

string outPathKey = "../DenkPlusPlus/Output/Keys.txt", outPathOutput = "../DenkPlusPlus/Output/Output.txt";
list<DataTypesClass::ProtocolTypesClass::Key> ProcessData::ext_keys;
list<DataTypesClass::ProtocolTypesClass::Key>::iterator iteratorKeys;
list<DataTypesClass::ProtocolTypesClass::BufferKey>::iterator iteratorBufferKeys;
list<DataTypesClass::ProtocolTypesClass::BufferKey> ProcessData::ext_bufferKeys;
list<string> ProcessData::ext_processedData, ProcessData::ext_processedBufferData;


void EncryptClass::encrypt() {
    auto start = chrono::high_resolution_clock::now();
    Protocols::EncryptClass::processData();
    Protocols::EncryptClass::bufferData();
    Protocols::EncryptClass::writeDataToFile();
    //Protocols::EncryptClass::expelDecrypted();
    if (ext_isDebugging) {
        Protocols::EncryptClass::expelCrypt();
        Protocols::EncryptClass::expelDecrypted();
    }

    auto finish = std::chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = (finish - start) * 1000;
    cout << endl << ProcessData::ext_iterationData << " Iterations" << endl << ext_messageData.size() << " chars"
         << endl;
    cout << "Rounded Elapsed Time: " << round(elapsed.count()) << " ms" << endl << "Full Elapsed Time: "
         << elapsed.count() << " ms" << endl << endl;

}

void EncryptClass::expelCrypt() {
    // Outputs each Key
    for (iteratorKeys = ext_keys.begin(); iteratorKeys != ext_keys.end(); iteratorKeys++) {
        cout << iteratorKeys->letter << "||" << iteratorKeys->shuffle << endl;
    }

    // Outputs encrypted letter
    if (ext_isDebugging) cout << ext_processedData.size() << endl;
    for (auto const &i: ext_processedData) {
        std::cout << i << std::endl;
    }
}

void EncryptClass::processData() {
    // Gets Keys
    list<char> used;
    DataTypesClass::ProtocolTypesClass::Key temporary;
    for (char c: ext_messageData) {
        if (!(find(used.begin(), used.end(), c) != used.end())) {
            temporary.letter = c;
            temporary.shuffle = KennyLibraries::Get::randomString(ext_iterationData);
            ext_keys.push_back(temporary);
            used.push_back(c);
        }
    }

    // Encrypt with Keys
    if (ext_isDebugging) cout << "size of message " << ext_messageData.size() << endl;
    for (char c: ext_messageData) {
        for (iteratorKeys = ext_keys.begin(); iteratorKeys != ext_keys.end(); iteratorKeys++) {
            if (iteratorKeys->letter == c)
                ext_processedData.push_back(iteratorKeys->shuffle);
        }
    }
}

void EncryptClass::writeDataToFile() {
    // Writes to Output
    ofstream outputFile(outPathOutput);
    for (string const &s: ext_processedData) { outputFile << s; }
    outputFile.close();

    // Writes to Key
    ofstream keyFile(outPathKey);
    for (iteratorKeys = ext_keys.begin(); iteratorKeys != ext_keys.end(); iteratorKeys++) {
        keyFile << iteratorKeys->letter << " " << iteratorKeys->shuffle << " " << endl;
    }
    keyFile.close();
}

void EncryptClass::expelDecrypted() {
    // Outputs each encrypted letter translated
    for (string const &s: ext_processedData) {
        for (iteratorKeys = ext_keys.begin(); iteratorKeys != ext_keys.end(); iteratorKeys++) {
            if (iteratorKeys->shuffle == s) { cout << iteratorKeys->letter; }
        }
    }
}

void EncryptClass::bufferData() {
    list<string> used, localTranslated;
    string carrier;
    DataTypesClass::ProtocolTypesClass::BufferKey carrier1;
    cout << ProcessData::ext_messageData << endl;
    int i = -1;
    for (string const &s: ext_processedData) {
        if ((i % 2) == 0) {
            carrier1.shuffle[1] = s;
            carrier1.reShuffle = KennyLibraries::Get::randomString(3);
           //CHECK FOR USED
            ProcessData::ext_processedBufferData.push_back(carrier1.reShuffle);
            ProcessData::ext_bufferKeys.push_back(carrier1);

            carrier = "";

        } else carrier1.shuffle[0] = s;

        i++;
    }

    for (iteratorBufferKeys = ext_bufferKeys.begin();
         iteratorBufferKeys != ext_bufferKeys.end(); iteratorBufferKeys++) {
        if (ext_isDebugging) cout << iteratorBufferKeys->reShuffle << " is the equivalent to " << iteratorBufferKeys->shuffle[0] << iteratorBufferKeys->shuffle[1] << endl;
    }

    for (string const &s: ext_processedBufferData){
        if (ext_isDebugging) cout << endl << s << "   " << endl;
        for (iteratorBufferKeys = ext_bufferKeys.begin(); iteratorBufferKeys != ext_bufferKeys.end(); iteratorBufferKeys++){
            if(iteratorBufferKeys->reShuffle == s){
                if (ext_isDebugging) cout << iteratorBufferKeys->shuffle[0] << "   " << iteratorBufferKeys->shuffle[1];
                localTranslated.push_back(iteratorBufferKeys->shuffle[0]);
                localTranslated.push_back(iteratorBufferKeys->shuffle[1]);
            }
        }

    }
    if (ext_isDebugging) cout << endl;
    for (string const &s: localTranslated) {
        for (iteratorKeys = ext_keys.begin(); iteratorKeys != ext_keys.end(); iteratorKeys++) {
            if (iteratorKeys->shuffle == s) {  cout << iteratorKeys->letter; }
        }
    }


}
