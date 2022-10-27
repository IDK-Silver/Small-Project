# project basic setup
project(Looking_For_Encryption LANGUAGES CXX)
cmake_minimum_required(VERSION 3.2)

# using conan package manager and run conan setup
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

# make executable using project source code
add_executable(Looking_For_Encryption src/main.cpp)

# link lib to executable
target_link_libraries(Looking_For_Encryption ${CONAN_LIBS})
