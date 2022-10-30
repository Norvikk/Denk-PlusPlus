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
using namespace EncryptData;

// Variable declaration field -->
int bufferSizeThreshold;
string outPathKey = "../DenkPlusPlus/Output/Keys.txt", outPathOutput = "../DenkPlusPlus/Output/Output.txt";
list<DataTypesClass::ProtocolTypesClass::Key> EncryptData::ext_keys;
list<DataTypesClass::ProtocolTypesClass::Key>::iterator iteratorKeys;
list<DataTypesClass::ProtocolTypesClass::BufferKey>::iterator iteratorBufferKeys;
list<DataTypesClass::ProtocolTypesClass::BufferKey> EncryptData::ext_bufferKeys;
list<string> EncryptData::ext_processedData, EncryptData::ext_processedBufferData;
list<long> EncryptData::ext_decentralizedData;

// Root for sub-functions -->
void EncryptClass::encrypt() {
    bufferSizeThreshold = EncryptData::ext_iterationData * 4;
    // NOTICE: Any output to the console before the FINISH variable is called drastically increases compilation time
    std::cout << "[" << EncryptData::ext_iterationData << "] Iterations" << endl;
    std::cout << "[" << bufferSizeThreshold << "] Buffer Iterations " << endl;
    std::cout << "[" << ext_messageData.size() << "] Unit long decentralizer" << endl;
    std::cout << "------------------------------------------------------" << endl;
    /* DiagnosticsData timer --> */ auto rootStart = chrono::high_resolution_clock::now();

    KennyLibraries::DiagnosticsTasks::getDiagnosticTimer("Processing phase (1/4)", (vFunctionCall) processData);
    KennyLibraries::DiagnosticsTasks::getDiagnosticTimer("Buffering phase (2/4)", (vFunctionCall) bufferData);
    KennyLibraries::DiagnosticsTasks::getDiagnosticTimer("Decentralizing (3/4)", (vFunctionCall) decentralize);
    KennyLibraries::DiagnosticsTasks::getDiagnosticTimer("Writing phase (4/4)", (vFunctionCall) writeDataToFile);


    if (ext_isDebugging) {
        Protocols::EncryptClass::expelCrypt();
        Protocols::EncryptClass::expelDecrypted();
    }

    // DiagnosticsData timer output -->
    auto finish = std::chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = (finish - rootStart) * 1000;
    KennyLibraries::DiagnosticsTasks::setDiagnosticDataToOutput();
    std::cout << "------------------------------------------------------" << endl;
    std::cout << "Rounded Time: " << round(elapsed.count()) << " ms" << " => " << elapsed.count() << " ms"<< endl;
    std::cout << "------------------------------------------------------" << endl << endl << endl;
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
            temporary.shuffle = KennyLibraries::Tools::Get::randomString(ext_iterationData);
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

    // Writes to Key
    ofstream keyFile(outPathKey);
    for (iteratorKeys = ext_keys.begin(); iteratorKeys != ext_keys.end(); iteratorKeys++) {
        keyFile << iteratorKeys->letter << "_" << iteratorKeys->shuffle << endl;
    }
    keyFile << "SPLIT" << endl;
    for (iteratorBufferKeys = ext_bufferKeys.begin();
         iteratorBufferKeys != ext_bufferKeys.end(); iteratorBufferKeys++) {
        keyFile << iteratorBufferKeys->shuffle[0] << iteratorBufferKeys->shuffle[1] << "_"
                << iteratorBufferKeys->reShuffle << endl;
    }
    keyFile.close();

    // Writes to Output
    ofstream outputFile(outPathOutput);
    for (const auto &a: EncryptData::ext_decentralizedData) outputFile << a;
    outputFile.close();
}

// Outputs each encrypted letter translated -->
void EncryptClass::expelDecrypted() {
    for (string const &s: ext_processedData) {
        for (iteratorKeys = ext_keys.begin(); iteratorKeys != ext_keys.end(); iteratorKeys++) {
            if (iteratorKeys->shuffle == s) { cout << iteratorKeys->letter; }
        }
    }
}

// Links 2 encrypted entries into a short lengthened single use buffer key -->
void EncryptClass::bufferData() {
    list<string> used, localTranslated;

    DataTypesClass::ProtocolTypesClass::BufferKey carrier1;
    int i = -1;
    for (string const &s: ext_processedData) {
        if ((i % 2) == 0) {
            carrier1.shuffle[1] = s;
            carrier1.reShuffle = KennyLibraries::Tools::Get::randomString(bufferSizeThreshold);
            EncryptData::ext_processedBufferData.push_back(carrier1.reShuffle);
            EncryptData::ext_bufferKeys.push_back(carrier1);
        } else carrier1.shuffle[0] = s;
        i++;
    }
/*
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
    for (string const &s: localTranslated) {
        for (iteratorKeys = ext_keys.begin(); iteratorKeys != ext_keys.end(); iteratorKeys++) {
            if (iteratorKeys->shuffle == s) { cout << iteratorKeys->letter; }
        }
    }
    std::cout << " [Decrypted (DEBUGGING)]";
    */
}

void EncryptClass::decentralize() {
    for (string const &s: EncryptData::ext_processedBufferData) {
        for (char const &c: s) {
            ext_decentralizedData.push_back((long) c + EncryptData::ext_messageData.size());
        }
    }
}

