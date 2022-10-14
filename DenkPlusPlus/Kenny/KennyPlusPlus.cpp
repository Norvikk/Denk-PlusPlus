
#include "KennyPlusPlus.h"

namespace KennyLibraries {
    string Get::randomString(int len) {
        static const char alphanum[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        string tmp_s;
        for (int i = 0; i < len; ++i) { tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)]; }
        return tmp_s;
    }
}