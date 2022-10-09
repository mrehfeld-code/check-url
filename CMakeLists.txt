cmake_minimum_required(VERSION 3.20)

project(check-url)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../bin")

set(SOURCE_FILES src/main.cpp)
add_executable(check-url ${SOURCE_FILES})

target_link_libraries(check-url PUBLIC "curl")
