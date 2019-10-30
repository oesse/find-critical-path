cmake_minimum_required(VERSION 3.12)
project(CriticialPathFinder VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
list(PREPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

find_package(Boost 1.71 REQUIRED)

include(Testing)

add_subdirectory(src)
