cmake_minimum_required(VERSION 3.16)
project(TempData)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(TempData
        Data.cpp
        Data.h
        DebugMacros.h
        HTTPSRedirect.cpp
        HTTPSRedirect.h
        Rfid.cpp
        Rfid.h
        TempData.ino
        WifiSetup.cpp
        WifiSetup.h
        wiring.h)
