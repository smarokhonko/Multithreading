cmake_minimum_required(VERSION 3.10)

project (deadlock VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

set(SOURCES )

find_package(Threads REQUIRED)

add_executable(deadlock main.cpp ${SOURCES})

target_link_libraries(deadlock Threads::Threads)