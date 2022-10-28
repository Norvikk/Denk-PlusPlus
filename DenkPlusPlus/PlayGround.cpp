#include <iostream>
#include "DataTypes/DataTypes.h"
#include "sysinfoapi.h"
#include "list"
#include <algorithm>
#include <chrono>

using namespace std;
using namespace DataTypes;

// Test field for ideas -->
namespace Playground {
    static void MainPlayground() {
        auto start = chrono::high_resolution_clock::now();

        auto finish = std::chrono::high_resolution_clock::now();
        chrono::duration<double> elapsed = (finish - start) * 1000;
        cout << endl << "Elapsed time: " << elapsed.count() << " ms\n";
    }

}

