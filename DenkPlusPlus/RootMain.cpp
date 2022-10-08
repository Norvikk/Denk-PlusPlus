#include <iostream>
#include "Protocols/Protocols.h"
#include "PlayGround.cpp"

using namespace std;
using namespace Protocols;
using namespace Playground;


int main() {
    // Playground::MainPlayground();

    cout << "Denk-PlusPlus by Norvik | V. 1" << endl;
    string protocol, messageData, iterationData, brickedDataPath, keysDataPath;


    cout << "[1] Encrypt\n[2] Decrypt" << endl;
    cin >> protocol;

    if (protocol == "1") {
        cout << "Message to encrypt:" << endl;
        cin >> messageData;

        cout << "Iteration count: (at least 10)" << endl;
        cin >> iterationData;

        if (stoi(iterationData) <= 10) throw invalid_argument(iterationData + " is not more than 10");
        Protocols::EncryptClass::encrypt(messageData, stoi(iterationData));


    } else if (protocol == "2") {
        cout << "Path to encrypted .txt file:" << endl;
        cin >> brickedDataPath;

        cout << "Path to keys .txt file:" << endl;
        cin >> keysDataPath;
        Protocols::DecryptClass::decrypt(brickedDataPath, keysDataPath);


    } else {
        throw invalid_argument(protocol + " is not identified as a protocol index");
    }


    return 0;
}
