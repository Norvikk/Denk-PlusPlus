cmake_minimum_required(VERSION 3.23)
project(Denk_PlusPlus)

set(CMAKE_CXX_STANDARD 14)

add_executable(Denk_PlusPlus
        DenkPlusPlus/RootMain.cpp DenkPlusPlus/Protocols/Encrypt.cpp DenkPlusPlus/Protocols/Protocols.h DenkPlusPlus/Protocols/Decrypt.cpp DenkPlusPlus/Protocols/DataTypes/DataTypes.h DenkPlusPlus/PlayGround.cpp DenkPlusPlus/Protocols/DataTypes/UniversalData.h)
