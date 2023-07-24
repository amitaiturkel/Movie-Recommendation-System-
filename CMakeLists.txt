cmake_minimum_required(VERSION 3.16)
project(ex5_amitat_turkel)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
add_executable(ex5_amitat_turkel
        Movie.cpp
        Movie.h
        User.cpp
        User.h
        RecommendationSystem.cpp
        RecommendationSystem.h
        UsersLoader.cpp
        UsersLoader.h
        RecommendationSystemLoader.cpp
        RecommendationSystemLoader.h
        print_main.cpp
        test.cpp test.cpp)
