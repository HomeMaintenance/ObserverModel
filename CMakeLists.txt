cmake_minimum_required(VERSION 3.20)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

project(ObserverModel)

add_subdirectory(test)

add_library(ObserverModel
    Observer.h
    Observer.cpp
    Subject.h
    Subject.cpp
)
target_include_directories(ObserverModel PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
