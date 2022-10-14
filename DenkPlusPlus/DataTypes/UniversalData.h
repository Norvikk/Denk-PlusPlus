#pragma once

#include "list"

using namespace std;
using namespace DataTypes;

namespace ProcessData {
    extern string ext_messageData, ext_brickedDataPath, ext_keysDataPath;
    extern int ext_iterationData;
    extern list <DataTypesClass::ProtocolTypesClass::Key> ext_keys;
    extern list <string> ext_processedData;
    extern bool ext_isDebugging;
}

