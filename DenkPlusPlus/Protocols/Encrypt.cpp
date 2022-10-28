// Sorted import field -->
#include "../DataTypes/DataTypes.h"
#include "../DataTypes/UniversalData.h"
#include "../Kenny/KennyPlusPlus.h"
#include "Protocols.h"
#include "list"
#include "cmath"
#include <iostream>
#include <chrono>
#include <fstream>
#include <string>
#include <algorithm>
#include <direct.h>


// Namespace import declaration field -->
using namespace KennyLibraries; // Versioned to this project
using namespace Protocols;
using namespace DataTypes;
using namespace ProcessData;

// Variable declaration field -->
string outPathKey = "../DenkPlusPlus/Output/Keys.txt", outPathOutput = "../DenkPlusPlus/Output/Output.txt";
list<DataTypesClass::ProtocolTypesClass::Key> ProcessData::ext_keys;
list<DataTypesClass::ProtocolTypesClass::Key>::iterator iteratorKeys;
list<DataTypesClass::ProtocolTypesClass::BufferKey>::iterator iteratorBufferKeys;
list<DataTypesClass::ProtocolTypesClass::BufferKey> ProcessData::ext_bufferKeys;
list<string> ProcessData::ext_processedData, ProcessData::ext_processedBufferData;


// Root for sub-functions -->
void EncryptClass::encrypt() {
    // NOTICE: Any output to the console before the FINISH variable is called drastically increases compilation time
    std::cout << ProcessData::ext_iterationData << " Iterations -> " << ext_messageData.size() << " chars" << endl;
    std::cout << "------------------------------------------------------" << endl;
    /* Diagnostics timer --> */ auto rootStart = chrono::high_resolution_clock::now();

    auto start1 = chrono::high_resolution_clock::now();
    Protocols::EncryptClass::processData();
    chrono::duration<double> elapsed1 = (std::chrono::high_resolution_clock::now() - start1) * 1000;

    auto start2 = chrono::high_resolution_clock::now();
    Protocols::EncryptClass::bufferData();
    chrono::duration<double> elapsed2 = (std::chrono::high_resolution_clock::now() - start2) * 1000;

    auto start3 = chrono::high_resolution_clock::now();
    Protocols::EncryptClass::writeDataToFile();
    chrono::duration<double> elapsed3 = (std::chrono::high_resolution_clock::now() - start3) * 1000;

    if (ext_isDebugging) {
        Protocols::EncryptClass::expelCrypt();
        Protocols::EncryptClass::expelDecrypted();
    }

    // Diagnostics timer output -->
    auto finish = std::chrono::high_resolution_clock::now();
    cout << "processData compiled in        => " << round(elapsed1.count()) << " ms" << endl
         << "bufferData compiled in         => " << round(elapsed2.count()) << " ms" << endl
         << "writeDataToFile compiled in    => " << round(elapsed3.count()) << " ms" << endl;
    chrono::duration<double> elapsed = (finish - rootStart) * 1000;
    std::cout << "------------------------------------------------------" << endl;
    std::cout << "Rounded Time: " << round(elapsed.count()) << " ms" << " => " << elapsed.count() << " ms";
}

// Output every processed therefore encrypted data -->
void EncryptClass::expelCrypt() {
    // Outputs each Key
    for (iteratorKeys = ext_keys.begin(); iteratorKeys != ext_keys.end(); iteratorKeys++) {
        std::cout << iteratorKeys->letter << "||" << iteratorKeys->shuffle << endl;
    }

    // Outputs encrypted letter
    for (auto const &i: ext_processedData) {
        std::cout << i << endl;
    }
}

// Standard obfuscating of each character -->
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
    for (char c: ext_messageData) {
        for (iteratorKeys = ext_keys.begin(); iteratorKeys != ext_keys.end(); iteratorKeys++) {
            if (iteratorKeys->letter == c)
                ext_processedData.push_back(iteratorKeys->shuffle);
        }
    }
}

// Create a folder and 2 sub-files for the keys&buffer and the encrypted string -->
void EncryptClass::writeDataToFile() {
    // Create directory
    _mkdir("../DenkPlusPlus/Output");

    // Writes to Output
    ofstream outputFile(outPathOutput);
    for (string const &s: ext_processedData) { outputFile << s; }
    outputFile.close();

    // Writes to Key
    ofstream keyFile(outPathKey);
    for (iteratorKeys = ext_keys.begin(); iteratorKeys != ext_keys.end(); iteratorKeys++) { keyFile << iteratorKeys->letter << " " << iteratorKeys->shuffle << " " << endl;}
    keyFile << endl  << "SPLIT" << endl << endl;
    for (iteratorBufferKeys = ext_bufferKeys.begin(); iteratorBufferKeys != ext_bufferKeys.end(); iteratorBufferKeys++) { keyFile << iteratorBufferKeys->shuffle[0] << iteratorBufferKeys->shuffle[1] << " " << iteratorBufferKeys->reShuffle << " " << endl;}
    keyFile.close();
}

// Outputs each encrypted letter translated -->
void EncryptClass::expelDecrypted() {
    for (string const &s: ext_processedData) {
        for (iteratorKeys = ext_keys.begin(); iteratorKeys != ext_keys.end(); iteratorKeys++) {
            if (iteratorKeys->shuffle == s) { cout << iteratorKeys->letter; }
        }
    }
}
add global used entry
// Links 2 encrypted entries into a short lengthened single use buffer key -->
void EncryptClass::bufferData() {
    list<string> used, localTranslated;

    DataTypesClass::ProtocolTypesClass::BufferKey carrier1;
    int i = -1;
    for (string const &s: ext_processedData) {
        if ((i % 2) == 0) {
            carrier1.shuffle[1] = s;
            carrier1.reShuffle = KennyLibraries::Get::randomString(64);
            ProcessData::ext_processedBufferData.push_back(carrier1.reShuffle);
            ProcessData::ext_bufferKeys.push_back(carrier1);
        } else carrier1.shuffle[0] = s;
        i++;
    }

    for (iteratorBufferKeys = ext_bufferKeys.begin();
         iteratorBufferKeys != ext_bufferKeys.end(); iteratorBufferKeys++) {
    }

    for (string const &s: ext_processedBufferData) {
        for (iteratorBufferKeys = ext_bufferKeys.begin();
             iteratorBufferKeys != ext_bufferKeys.end(); iteratorBufferKeys++) {
            if (iteratorBufferKeys->reShuffle == s) {
                localTranslated.push_back(iteratorBufferKeys->shuffle[0]);
                localTranslated.push_back(iteratorBufferKeys->shuffle[1]);
            }
        }

    }

    // Uses de-buffered entries and locally decrypts them with the keys -->
   /* for (string const &s: localTranslated) {
        for (iteratorKeys = ext_keys.begin(); iteratorKeys != ext_keys.end(); iteratorKeys++) {
            if (iteratorKeys->shuffle == s) { cout << iteratorKeys->letter; }
        }
    }
    std::cout << " [Decrypted (DEBUGGING)]";
    */
}

