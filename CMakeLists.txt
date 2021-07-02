cmake_minimum_required(VERSION 3.16)
project(HexGameAssignment)

set(CMAKE_CXX_STANDARD 14)

add_executable(HexGameAssignment main.cpp RandomPlayer.h MonteCarloPlayer.h Cell.h SmartPlayer.h)