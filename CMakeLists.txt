cmake_minimum_required(VERSION 3.19)
project(DeepMiner)

set(CMAKE_CXX_STANDARD 14)

add_executable(DeepMiner main.cpp mine.cpp mine.h Robot.cpp Robot.h GoldDigger.cpp GoldDigger.h position.cpp position.h AllrounderDigger.cpp AllrounderDigger.h Leprechaun.cpp Leprechaun.h)

find_package(Catch2 REQUIRED)
add_executable(tests test.cpp)
target_link_libraries(tests PRIVATE Catch2::Catch2)

SET(CMAKE_CXX_FLAGS -pthread)

target_link_libraries( DeepMiner pthread )