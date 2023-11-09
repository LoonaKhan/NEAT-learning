cmake_minimum_required(VERSION 3.23)
project(demo)

set(CMAKE_CXX_STANDARD 20)

# libraries
set(SFML_LIBS sfml-graphics sfml-window sfml-system sfml-audio)

add_executable(nn_test tests/nn_test.cpp nn_models/node.cpp nn_models/node.h nn_models/network.cpp nn_models/network.h random.hpp)
add_executable(mariobros_training mariobros_training.cpp models/player.h models/player.cpp models/obstacle.cpp models/obstacle.h textures/textures.cpp textures/textures.h music/music.cpp music/music.h config/config.cpp config/config.h nn_models/node.cpp nn_models/node.h nn_models/network.cpp nn_models/network.h random.hpp objects.cpp objects.h text/text.cpp text/text.h)

target_link_libraries(mariobros_training ${SFML_LIBS})