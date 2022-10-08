#include <iostream>
#include "Protocols/Protocols.h"
#include "Protocols/DataTypes/UniversalData.h"
#include "PlayGround.cpp"

using namespace std;
using namespace Protocols;
using namespace Playground;

int ext_iterationData;
string ext_messageData, brickedDataPath, keysDataPath;
string protocol = "1";

int main() {
    srand(time(NULL));
    // Playground::MainPlayground();

    cout << "Denk-PlusPlus by Norvik | V. 1" << endl;

    ext_iterationData = 15;
    ext_messageData = "asdfasdf";



   // cout << "[1] Encrypt\n[2] Decrypt" << endl;
   // cin >> protocol;

    if (protocol == "1") {
        //cout << "Message to encrypt:" << endl;
        //cin >> ext_messageData;

       // cout << "Iteration count: (at least 10)" << endl;
       // cin >> EXT_iterationData;

       // if (stoi(EXT_iterationData) <= 10) throw invalid_argument(EXT_iterationData + " is not more than 10");
        Protocols::EncryptClass::encrypt();


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
