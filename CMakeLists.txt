cmake_minimum_required(VERSION 3.29)

# Set the project name
project(RTIOW-cpp)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the executable
add_executable(RTIOW-cpp source/main.cpp)