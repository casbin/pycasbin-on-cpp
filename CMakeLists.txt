cmake_minimum_required(VERSION 3.12)
project(pycasbin_cpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Find Python
find_package(Python COMPONENTS Interpreter Development REQUIRED)

# Add pybind11
add_subdirectory(third_party/pybind11)

# Add casbin-cpp
set(CASBIN_BUILD_TEST OFF CACHE BOOL "Build casbin-cpp tests")
set(CASBIN_BUILD_BENCHMARK OFF CACHE BOOL "Build casbin-cpp benchmarks")
add_subdirectory(third_party/casbin-cpp)

# Create the Python module
pybind11_add_module(_pycasbin_cpp src/bindings.cpp)

# Link against casbin
target_link_libraries(_pycasbin_cpp PRIVATE casbin)

# Include casbin headers
target_include_directories(_pycasbin_cpp PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/casbin-cpp/include
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/casbin-cpp/casbin
)

# Set output directory
set_target_properties(_pycasbin_cpp PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}
)
