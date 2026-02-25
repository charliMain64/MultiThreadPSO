cmake_minimum_required(VERSION 4.0)
project(pso)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find packages
find_package(Eigen3 REQUIRED)
find_package(OpenMP REQUIRED)

# Define the executable (removed the duplicate main.cpp)
add_executable(pso main.cpp)

# Link both OpenMP and Eigen using Modern CMake targets
target_link_libraries(pso
        PRIVATE
        Eigen3::Eigen
        OpenMP::OpenMP_CXX
)