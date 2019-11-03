cmake_minimum_required(VERSION 3.12)
project(CriticialPathFinder VERSION 1.0.0 LANGUAGES CXX)

option(ENABLE_CLANG_TIDY "Enable static code analysis with clang-tidy" OFF)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
list(PREPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)

find_package(Boost 1.71 REQUIRED)

if(ENABLE_CLANG_TIDY)
  include(ClangTidy)
endif()

include(Testing)
include(MaintainerBuild)

add_subdirectory(src)
