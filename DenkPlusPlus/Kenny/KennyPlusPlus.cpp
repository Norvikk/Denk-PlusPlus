#include "KennyPlusPlus.h"
#include <chrono>
#include "math.h"
#include "KennyPlusPlus.h"
#include "../Protocols/Protocols.h"

list<KennyLibraries::Data::Diagnostics::DataStyles::DiagnosticsInfo> KennyLibraries::Data::Diagnostics::ext_diagnosticsTimers;
list<KennyLibraries::Data::Diagnostics::DataStyles::DiagnosticsInfo>::iterator diagnosticsIteratorTimers;


namespace KennyLibraries {

    string Get::randomString(int len) {
        static const char alphanum[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890!@#$%^&*()`~-_=+[{]{|;:'\",<>/?";
        string tmp_s;
        for (long i = 0; i < len; ++i) { tmp_s += alphanum[rand() % 92]; } //93 - 1 = letter amount in char
        return tmp_s;
    }

    void Diagnostics::getDiagnosticTimer(const string& name, vFunctionCall funct2) {
        /* Diagnostics timer --> */
        auto rootStart = chrono::high_resolution_clock::now();
        //Protocols::EncryptClass::processData();
        funct2(0);
        auto finish = std::chrono::high_resolution_clock::now();
        chrono::duration<double> elapsed = (finish - rootStart) * 1000;


        KennyLibraries::Data::Diagnostics::DataStyles::DiagnosticsInfo carrier1;
        carrier1.name = name;
        carrier1.runTime = elapsed.count();
        KennyLibraries::Data::Diagnostics::ext_diagnosticsTimers.push_back(carrier1);

    }

    void Diagnostics::setDiagnosticDataToOutput() {

        for (diagnosticsIteratorTimers = KennyLibraries::Data::Diagnostics::ext_diagnosticsTimers.begin(); diagnosticsIteratorTimers != KennyLibraries::Data::Diagnostics::ext_diagnosticsTimers.end(); diagnosticsIteratorTimers++ ){
            std::cout << diagnosticsIteratorTimers->name << " has compiled in\t\t=> " << diagnosticsIteratorTimers->runTime << " ms (" << round(diagnosticsIteratorTimers->runTime) << " ms)" << std::endl;
        }
    }

}