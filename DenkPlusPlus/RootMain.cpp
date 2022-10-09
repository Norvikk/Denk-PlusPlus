#include <iostream>
#include "Protocols/Protocols.h"
#include "PlayGround.cpp"
#include "Protocols/DataTypes/UniversalData.h"


using namespace std;
using namespace Protocols;
using namespace Playground;
using namespace ProcessData;


int    ProcessData::ext_iterationData = 512;
string ProcessData::ext_messageData = "This message should be fully readable by the time it is decrypted, well hopefully at least.";
string ProcessData::ext_brickedDataPath;
string ProcessData::ext_keysDataPath;


string protocol = "1";
bool isPlayground = false;


int main() {
    srand(GetTickCount());
    // cout << "Denk-PlusPlus by Norvik | V. 1" << endl;
    if (isPlayground) {
        Playground::MainPlayground();
        cin >> ext_brickedDataPath;
    } else {
        Protocols::EncryptClass::encrypt();
        cin >> protocol;
    }

    cout << "[1] Encrypt\n[2] Decrypt" << endl;
    if (protocol == "1") {
        cout << "Message to encrypt:" << endl;
        cin >> ext_messageData;
        cout << "Iteration count: (at least 10)" << endl;
        cin >> ext_iterationData;

        Protocols::EncryptClass::encrypt();
    } else if (protocol == "2") {
        cout << "Path to encrypted .txt file:" << endl;
        cin >> ext_brickedDataPath;
        cout << "Path to keys .txt file:" << endl;
        cin >> ext_keysDataPath;

        Protocols::DecryptClass::decrypt();

    } else { throw invalid_argument(protocol + " is not identified as a protocol index"); }
    return 0;
}
