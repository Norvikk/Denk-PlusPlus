#include <iostream>
#include "Protocols/Protocols.h"
#include "PlayGround.cpp"
#include "DataTypes/UniversalData.h"


using namespace std;
using namespace Protocols;
using namespace Playground;
using namespace ProcessData;

string ProcessData::ext_brickedDataPath, ProcessData::ext_keysDataPath, protocol;

bool ProcessData::ext_isDebugging = false;
bool isPlayground = false;
int ProcessData::ext_iterationData = 10;
string ProcessData::ext_messageData = "abcd";

int main() {
    srand(GetTickCount());
    if (isPlayground) Playground::MainPlayground();
    else Protocols::EncryptClass::encrypt();

    cin >> protocol;
    cout << "Denk-PlusPlus by Norvik | V. 1" << endl;
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
