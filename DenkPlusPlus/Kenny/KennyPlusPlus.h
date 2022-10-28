#pragma once

#include <iostream>
#include "../DataTypes/DataTypes.h"
#include "list"

typedef void (* vFunctionCall)(int args);

using namespace std;
using namespace DataTypes;

namespace KennyLibraries {

    namespace Data {
        namespace Diagnostics {
            class DataStyles {
            public:
                struct DiagnosticsInfo {
                    string name;
                    double runTime;
                };
            };
            extern list <Diagnostics::DataStyles::DiagnosticsInfo> ext_diagnosticsTimers;
        }
    }

    class Get {
    public:
        static string randomString(int len);
    };

    class Diagnostics {
    public:
        static void getDiagnosticTimer(const string& name, vFunctionCall funct2);

        static void setDiagnosticDataToOutput();
    };

    class Loop {
    public:

    };

    class Output {
    public:

    };
}
