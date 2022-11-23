cmake_minimum_required(VERSION 3.24.2)
project(SimpleNeuron)
set(CMAKE_CXX_STANDARD 20)

add_subdirectory(src/opusutil)
add_subdirectory(src/randutil)

add_executable(neuron 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/neuron.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/neuron.cpp)

target_link_libraries(neuron PUBLIC opusutil randutil)

target_include_directories(neuron PUBLIC 
                           "${PROJECT_BINARY_DIR}" 
                           "${PROJECT_SOURCE_DIR}/src/randutil"
                           "${PROJECT_SOURCE_DIR}/src/opusutil")