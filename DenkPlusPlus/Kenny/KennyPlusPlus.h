#pragma once

#include <iostream>
#include "../DataTypes/DataTypes.h"
#include "list"

typedef void (* vFunctionCall)(int args);

using namespace std;
using namespace DataTypes;

namespace KennyLibraries {

    namespace Data {
        namespace DiagnosticsData {
            class Structs {
            public:
                struct DiagnosticsInfo {
                    string name;
                    double runTime;
                };
            };
            extern list <DiagnosticsData::Structs::DiagnosticsInfo> ext_diagnosticsTimers;
        }
    }
    namespace Tools{
        class Get {
        public:
            static string randomString(int len);
            static int randomInt(int minSize, int maxSize);
        };
    }


    class DiagnosticsTasks {
    public:
        static void getDiagnosticTimer(const string& name, vFunctionCall funct2);

        static void setDiagnosticDataToOutput();
    };
}
