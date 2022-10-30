#pragma once

#include "list"

using namespace std;
using namespace DataTypes;

namespace EncryptData {
    extern string ext_messageData, ext_brickedDataPath, ext_keysDataPath;
    extern int ext_iterationData;

    extern list <long> ext_decentralizedData;
    extern list <DataTypesClass::ProtocolTypesClass::Key> ext_keys;
    extern list <DataTypesClass::ProtocolTypesClass::BufferKey> ext_bufferKeys;
    extern list <string> ext_processedData, ext_processedBufferData;

    extern bool ext_isDebugging;
}

namespace DecryptData {

}


