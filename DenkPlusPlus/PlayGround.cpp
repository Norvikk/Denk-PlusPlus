#include <iostream>
#include "DataTypes/DataTypes.h"
#include "sysinfoapi.h"
#include "list"
#include <algorithm>
#include <chrono>

using namespace std;
using namespace DataTypes;

namespace Playground {
    static void MainPlayground() {
        auto start = chrono::high_resolution_clock::now();

        list<int> used;
        int carrier1;
        for (int I = 0; I < 1000000; I++) {
            used.push_back(rand() % 900);
        }


        auto finish = std::chrono::high_resolution_clock::now();
        chrono::duration<double> elapsed = (finish - start) * 1000;
        cout << endl << "Elapsed time: " << elapsed.count() << " ms\n";
    }

}

