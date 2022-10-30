#include "Protocols.h"
#include <iostream>
#include <chrono>
#include "cmath"
#include <fstream>
#include <string>
#include "../Kenny/KennyPlusPlus.h"
#include "../DataTypes/UniversalData.h"
#include <thread>


using namespace Protocols;
using namespace KennyLibraries;
using namespace EncryptData;

string unformattedBrickedOutput;
int bufferSize;
list<string> readyToDecryptWords;
list<DataTypesClass::ProtocolTypesClass::Key> keyStructure;
list<DataTypesClass::ProtocolTypesClass::BufferKey> bufferKeyStructure;

list<DataTypesClass::ProtocolTypesClass::Key>::iterator iterator_keyStructure;
list<DataTypesClass::ProtocolTypesClass::BufferKey>::iterator iterator_bufferKeyStructure;


void DecryptClass::decrypt() {
    auto rootStart = chrono::high_resolution_clock::now();
    KennyLibraries::DiagnosticsTasks::getDiagnosticTimer("Bricked reading phase (1/4)", (vFunctionCall) readBricked);
    KennyLibraries::DiagnosticsTasks::getDiagnosticTimer("Key reading phase (2/4)\t", (vFunctionCall) readKeys);
    KennyLibraries::DiagnosticsTasks::getDiagnosticTimer("Centralizing phase (3/4)", (vFunctionCall) centralize);
    KennyLibraries::DiagnosticsTasks::getDiagnosticTimer("Outputting phase (4/4)\t", (vFunctionCall) output);


    auto finish = std::chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = (finish - rootStart) * 1000;
    KennyLibraries::DiagnosticsTasks::setDiagnosticDataToOutput();
    std::cout << "------------------------------------------------------" << endl;
    std::cout << "Rounded Time: " << round(elapsed.count()) << " ms" << " => " << elapsed.count() << " ms" << endl;
    std::cout << "------------------------------------------------------" << endl;
}

void DecryptClass::readBricked() {
    ifstream brickedFile;

    brickedFile.open(EncryptData::ext_brickedDataPath, ios::out | ios::app | ios::binary);
    if (!brickedFile.is_open()) { throw invalid_argument("The file has not been opened"); }
    getline(brickedFile, unformattedBrickedOutput);
    brickedFile.close();
}


void DecryptClass::readKeys() {
    bool hasSplit;
    DataTypesClass::ProtocolTypesClass::Key KeyTemporal;
    DataTypesClass::ProtocolTypesClass::BufferKey BufferKeyTemporal;
    ifstream input(EncryptData::ext_keysDataPath);

    for (std::string line; getline(input, line);) {
        if (line == "SPLIT") { hasSplit = true; }

        if (!hasSplit) {
            char charOne;
            string wordTwo;
            bool delimiterMet = false;

            for (char x: line) {
                if (x == '_') { delimiterMet = true; }
                else if (!delimiterMet) { charOne = x; }
                else { wordTwo += x; }
            }
            KeyTemporal.shuffle = wordTwo;
            KeyTemporal.letter = charOne;
            wordTwo = "";
            keyStructure.push_back(KeyTemporal);
        } else {
            string doubleWordOne;
            string wordTwo;
            bool delimiterMet = false;

            for (char x: line) {
                if (x == '_') { delimiterMet = true; }
                else if (!delimiterMet) { doubleWordOne += x; }
                else { wordTwo += x; }
            }

            string doubleWordOne_WordOne;
            string doubleWordOne_WordTwo;
            int iterator = 0;

            for(char c: doubleWordOne){
                if (iterator < (doubleWordOne.size()/2)) doubleWordOne_WordOne += c;
                else doubleWordOne_WordTwo += c;
                iterator++;
            }

            BufferKeyTemporal.shuffle[0] = doubleWordOne_WordOne;
            BufferKeyTemporal.shuffle[1] = doubleWordOne_WordTwo;
            BufferKeyTemporal.reShuffle = wordTwo;
            bufferSize = doubleWordOne.length();
            doubleWordOne_WordOne = "";
            doubleWordOne_WordTwo = "";
            doubleWordOne = "";
            wordTwo = "";
            bufferKeyStructure.push_back(BufferKeyTemporal);
        }

    }
}

void DecryptClass::centralize() {
    list<char> centralizedLetters;
    int lengthNumber = 0;
    int num = 1;
    string str;
    char cha;
    int dictionarySize = unformattedBrickedOutput.length() / bufferSize / 3;


    for(char c: unformattedBrickedOutput){
        if((num % 3) == 0){
            str += c;
            cha = char(stoi(str) - dictionarySize);
            centralizedLetters.push_back(cha);
            num = 0;
            str = "";
        }
        else{
            str += c;
        }
        num++;
        lengthNumber++;
    }
    string word;
    int iterator = 1;
    list<string> bufferedEntry;
    for(char c: centralizedLetters){
        if((iterator % (bufferSize * 2) == 0)){
            word += c;
            bufferedEntry.push_back(word);
            word = "";
        } else{
            word += c;
        }

        iterator++;
    }

    for(string c: bufferedEntry){

        for(iterator_bufferKeyStructure = bufferKeyStructure.begin(); iterator_bufferKeyStructure != bufferKeyStructure.end(); iterator_bufferKeyStructure++){
            if (iterator_bufferKeyStructure->reShuffle == c){
                readyToDecryptWords.push_back(iterator_bufferKeyStructure->shuffle[0]);
                readyToDecryptWords.push_back(iterator_bufferKeyStructure->shuffle[1]);
            }
        }
    }

}

void DecryptClass::output() {
    for (string const &s: readyToDecryptWords) {
        for (iterator_keyStructure = keyStructure.begin(); iterator_keyStructure != keyStructure.end(); iterator_keyStructure++) {
            if (iterator_keyStructure->shuffle == s) { cout << iterator_keyStructure->letter; }
        }
    }

    cout << "\n\n";
}



