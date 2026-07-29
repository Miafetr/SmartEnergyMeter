cmake_minimum_required(VERSION 3.16)

project(MeterSimulator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(MeterSimulator
    src/main.cpp
    src/SensorSimulator.cpp
    src/SmartMeter.cpp
    src/TcpClient.cpp
)