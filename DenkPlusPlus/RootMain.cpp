#include <iostream>
#include "Protocols/Protocols.h"
#include "PlayGround.cpp"
#include "DataTypes/UniversalData.h"
#include "Kenny/KennyPlusPlus.h"
#include "thread"


using namespace std;
using namespace Protocols;
using namespace Playground;
using namespace EncryptData;
using namespace KennyLibraries;

//DECRYPT
string EncryptData::ext_brickedDataPath = "../DenkPlusPlus/Output/Output.txt", //Hard Coded
EncryptData::ext_keysDataPath = "../DenkPlusPlus/Output/Keys.txt"; //Hard coded
string protocol = "1"; //Hard coded

//ENCRYPT
bool EncryptData::ext_isDebugging = false; //Debugging
int EncryptData::ext_iterationData = 8; //Hard coded

string EncryptData::ext_messageData;

int main() {
    srand(GetTickCount());
    //ext_messageData = KennyLibraries::Tools::Get::randomString(KennyLibraries::Tools::Get::randomInt(100, 800));
    ext_messageData = "TestName TestPaswordItemsabababababababbaabbabababab \t TestName tESTpasswordafkjsdfskdfsdafsdafasdffdsffdsfdsasfdddasfds \t Testname GTGFGGFGFGFGFGFGFGFGF";
    if (ext_messageData.size() % 2 != 0) EncryptData::ext_messageData += " ";

    while (ext_messageData.size() % 3 != 0 && ext_messageData.size() % 3 != 0) {
        ext_messageData += "-";
    }


    Protocols::EncryptClass::encrypt();
    Protocols::DecryptClass::decrypt();


    cin >> protocol;
    cout << "Denk-PlusPlus by Norvik | V. 1" << endl;
    cout << "[1] Encrypt\n[2] Decrypt" << endl;
    cin >> protocol;

    if (protocol == "1") {
        cout << "Message to encrypt:" << endl;
        cin >> EncryptData::ext_messageData;
        cout
                << "Iterations:\nLow [16] [32]\nMedium [64] [128]\nHigh [256] [512]\nAbsurd [1024+]\nCustom [Any other number]\n----------------\nInput the number  "
                << endl;
        cin >> EncryptData::ext_iterationData;
        Protocols::EncryptClass::encrypt();
    } else if (protocol == "2") {
        cout << "Path to encrypted .txt file:" << endl;
        cin >> EncryptData::ext_brickedDataPath;
        cout << "Path to keys .txt file:" << endl;
        cin >> EncryptData::ext_keysDataPath;

        Protocols::DecryptClass::decrypt();
    } else { throw invalid_argument(protocol + " is not identified as a protocol index"); }

    return 0;
}
