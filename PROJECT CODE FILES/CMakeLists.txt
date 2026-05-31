cmake_minimum_required(VERSION 3.20)
project(CGPA_Calculator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(CGPA_Calculator
        main.cpp
        grading.cpp
        report.cpp
        functions.cpp
)
