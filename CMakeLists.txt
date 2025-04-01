cmake_minimum_required(VERSION 3.22)
project(patterns)

set(CMAKE_CXX_STANDARD 20)

add_executable(Facade Structural/Facade.cpp)
add_executable(Factory Сreational/Factory.cpp)
add_executable(Memento Behavioral/Memento.cpp)
add_executable(Builder Сreational/Builder.cpp)
add_executable(Singleton Сreational/Singleton.cpp)
