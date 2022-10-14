#include <iostream>
#include "Protocols/Protocols.h"
#include "PlayGround.cpp"
#include "DataTypes/UniversalData.h"


using namespace std;
using namespace Protocols;
using namespace Playground;
using namespace ProcessData;


bool ProcessData::ext_isDebugging = false, ProcessData::ext_isTestingSpeed = false,
    isPlayground = false;
int ProcessData::ext_iterationData = 1000;
string ProcessData::ext_brickedDataPath, ProcessData::ext_keysDataPath,
    ProcessData::ext_messageData = "1234567890qwertzuiopasdfghjklyxcvbnm",
    protocol = "1";


int main() {
    srand(GetTickCount());
    cout << "Denk-PlusPlus by Norvik | V. 1" << endl;
    if (isPlayground) Playground::MainPlayground();
    else Protocols::EncryptClass::encrypt();

    cout << "[1] Encrypt\n[2] Decrypt" << endl;
    cin >> protocol;
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
