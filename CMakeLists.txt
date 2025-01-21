cmake_minimum_required(VERSION 3.28)
project(ASK_fm)

set(CMAKE_CXX_STANDARD 17)

add_executable(ASK_fm main.cpp
        Configuration.cpp
        Questions.cpp
        Users.cpp
        Answer.cpp)
