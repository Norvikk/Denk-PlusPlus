#include "KennyPlusPlus.h"
#include <chrono>
#include <cmath>
#include "../Protocols/Protocols.h"

list<KennyLibraries::Data::DiagnosticsData::Structs::DiagnosticsInfo> KennyLibraries::Data::DiagnosticsData::ext_diagnosticsTimers;
list<KennyLibraries::Data::DiagnosticsData::Structs::DiagnosticsInfo>::iterator diagnosticsIteratorTimers;


namespace KennyLibraries {

    string KennyLibraries::Tools::Get::randomString(int len) {
        static const char alphanum[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890!@#$%^&*()`~-=+[{]{|;:'\",<>/?";
        string tmp_s;
        for (long i = 0; i < len; ++i) { tmp_s += alphanum[rand() % 91]; } //93 - 1 = letter amount in char
        return tmp_s;


    }

    void DiagnosticsTasks::getDiagnosticTimer(const string& name, vFunctionCall funct2) {
        /* DiagnosticsData timer --> */
        auto rootStart = chrono::high_resolution_clock::now();
        //Protocols::EncryptClass::processData();
        funct2(0);
        auto finish = std::chrono::high_resolution_clock::now();
        chrono::duration<double> elapsed = (finish - rootStart) * 1000;


        KennyLibraries::Data::DiagnosticsData::Structs::DiagnosticsInfo carrier1;
        carrier1.name = name;
        carrier1.runTime = elapsed.count();
        KennyLibraries::Data::DiagnosticsData::ext_diagnosticsTimers.push_back(carrier1);

    }

    void DiagnosticsTasks::setDiagnosticDataToOutput() {

        for (diagnosticsIteratorTimers = KennyLibraries::Data::DiagnosticsData::ext_diagnosticsTimers.begin(); diagnosticsIteratorTimers != KennyLibraries::Data::DiagnosticsData::ext_diagnosticsTimers.end(); diagnosticsIteratorTimers++ ){
            std::cout << diagnosticsIteratorTimers->name << " has compiled in\t\t=> " << diagnosticsIteratorTimers->runTime << " ms (" << round(diagnosticsIteratorTimers->runTime) << " ms)" << std::endl;
        }
        KennyLibraries::Data::DiagnosticsData::ext_diagnosticsTimers.clear();
    }

}