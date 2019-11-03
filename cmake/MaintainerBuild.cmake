set(CMAKE_CXX_FLAGS_MAINTAINER "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Wextra")

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Maintainer")
endif()

string(TOLOWER "${CMAKE_BUILD_TYPE}" build_type)
if(build_type STREQUAL "maintainer")
  message(STATUS "Maintainer build detected.")
endif()

