cmake_minimum_required(VERSION 4.0)
project(pso)

set(CMAKE_CXX_STANDARD 20)
set(EIGEN_DIR "/home/charli/Downloads/eigen-5.0.0")

if(NOT EXISTS ${EIGEN_DIR})
    message(FATAL_ERROR "Eigen directory not found: ${EIGEN_DIR}")
endif()

include_directories(${EIGEN_DIR})

add_executable(pso main.cpp)
