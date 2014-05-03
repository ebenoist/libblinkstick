include_directories(${gtest_SOURCE_DIR}/include)
set(test_sources blinkstick_tests.cc)

add_executable(unit_tests ${test_sources})
target_link_libraries(unit_tests gtest gtest_main)
target_link_libraries(unit_tests libblinkstick)

add_test(unit-tests unit_tests)
