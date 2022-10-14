#include "KennyPlusPlus.h"

namespace KennyLibraries {

    string Get::randomString(int len) {
        static const char alphanum[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890!@#$%^&*()`~-_=+[{]{|;:'\",<.>/?";
        string tmp_s;
        for (long i = 0; i < len; ++i) { tmp_s += alphanum[rand() % 92]; } //93 - 1 = letter amount in char
        return tmp_s;
    }
}