set(CMAKE_CXX_FLAGS_MAINTAINER "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Wextra")

set(default_build_type "Release")
if(EXISTS "${CMAKE_SOURCE_DIR}/.git")
  set(default_build_type "Maintainer")
endif()

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "Setting build type to '${default_build_type}' as none was specified.")

  set(CMAKE_BUILD_TYPE "${default_build_type}"
    CACHE STRING "Choose the type of build." FORCE)
  # Set the possible values of build type for cmake-gui
  set_property(CACHE CMAKE_BUILD_TYPE
    PROPERTY STRINGS "Maintainer" "Debug" "Release" "MinSizeRel" "RelWithDebInfo")

  set(ENABLE_CLANG_TIDY ON
    CACHE BOOL "Enable static code analysis with clang-tidy" FORCE)
endif()
