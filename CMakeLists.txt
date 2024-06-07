cmake_minimum_required(VERSION 3.23)
project(AizoGrafy)

set(CMAKE_CXX_STANDARD 23)

add_executable(AizoGrafy main.cpp Graph.cpp Graph.h Menu.cpp Menu.h Edges.cpp Edges.h  Algorithm.cpp Algorithm.h Simulation.cpp Simulation.h)
