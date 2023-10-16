cmake_minimum_required(VERSION 3.23)
project(demo)

set(CMAKE_CXX_STANDARD 20)

add_executable(demo main.cpp node.cpp node.h network.cpp network.h random.hpp)
