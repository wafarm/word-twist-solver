cmake_minimum_required(VERSION 3.10)
project(solver)
add_library(solver SHARED solver.cpp)
include_directories("C:\\Users\\qinyuyao\\AppData\\Local\\Programs\\Python\\Python311\\include")
link_directories("C:\\Users\\qinyuyao\\AppData\\Local\\Programs\\Python\\Python311\\libs")

target_link_libraries(solver "C:\\Users\\qinyuyao\\AppData\\Local\\Programs\\Python\\Python311\\libs\\python311.lib")
