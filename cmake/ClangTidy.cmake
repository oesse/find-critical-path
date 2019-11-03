find_program(CLANG_TIDY_PATH clang-tidy)
if(NOT CLANG_TIDY_PATH)
  message(FATAL_ERROR "Could not find \"clang-tidy\". \n"
                      "Add the installation prefix of \"clang-tidy\" to "
                      "CMAKE_PREFIX_PATH, set CMAKE_PROGRAM_PATH, or disable "
                      "clang-tidy by setting ENABLE_CLANG_TIDY=OFF.")
endif()

set(CMAKE_CXX_CLANG_TIDY ${CLANG_TIDY_PATH})
