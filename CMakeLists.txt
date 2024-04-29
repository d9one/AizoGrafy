cmake_minimum_required(VERSION 3.23)
project(AizoGrafy)

set(CMAKE_CXX_STANDARD 23)

add_executable(AizoGrafy main.cpp UndirectedGraph.cpp UndirectedGraph.h Menu.cpp Menu.h)
