cmake_minimum_required(VERSION 3.23)
project(demo)

set(CMAKE_CXX_STANDARD 20)

# libraries
set(SFML_LIBS sfml-graphics sfml-window sfml-system sfml-audio)

add_executable(nn_test nn_test.cpp node.cpp node.h network.cpp network.h random.hpp)
add_executable(sprite_test sprite_test.cpp player.h player.cpp)

target_link_libraries(sprite_test ${SFML_LIBS})