include_directories(${CMAKE_SOURCE_DIR})

add_executable(
        Calculator_test
        Calculator_test.cpp
)
target_link_libraries(
        Calculator_test
        PRIVATE CalcLib
        PRIVATE gtest gmock gtest_main
)
#1
include(GoogleTest)
gtest_discover_tests(Calculator_test)