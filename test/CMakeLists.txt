include_directories(
  ${COMMON_INCLUDES}
)

set(test_sources blinkstick_tests.c)

add_executable(unit_tests ${test_sources})
target_link_libraries(unit_tests libblinkstick seatest)

add_test(unit-tests unit_tests)
