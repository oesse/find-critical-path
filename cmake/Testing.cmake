include(CTest)
if(BUILD_TESTING)
  find_package(Catch2 2.10 REQUIRED)

  set(test_main_source ${PROJECT_BINARY_DIR}/test_main.cpp)
  if(NOT EXISTS ${test_main_source})
    file(WRITE ${test_main_source}
      "#define CATCH_CONFIG_MAIN\n"
      "#include <catch2/catch.hpp>\n"
    )
  endif()
  add_library(TestMain OBJECT ${test_main_source})
  target_link_libraries(TestMain PUBLIC Catch2::Catch2)

  function(add_test_case test_source_name library)
    string(REGEX REPLACE "^(.*)\\.cpp" "\\1" test_name "${test_source_name}")

    add_executable(${test_name} ${test_source_name})
    target_link_libraries(${test_name} PRIVATE ${library} TestMain)
    add_test(NAME ${test_name} COMMAND $<TARGET_FILE:${test_name}>)
  endfunction()
else()
  function(add_test_case test_name)
    # do nothing
  endfunction()
endif()

