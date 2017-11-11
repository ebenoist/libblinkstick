cmake_minimum_required (VERSION 2.6)

project (libblinkstick)

enable_testing()

find_package(PkgConfig REQUIRED)
pkg_search_module(HIDAPI REQUIRED hidapi)

link_libraries(${HIDAPI_LIBRARIES})
include_directories(PUBLIC ${HIDAPI_INCLUDE_DIRS})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/target)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/target)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/target)

set(COMMON_INCLUDES ${PROJECT_SOURCE_DIR}/src ${PROJECT_SOURCE_DIR}/seatest ${HIDAPI_INCLUDE_DIRS})

add_subdirectory(src)

if (test)
  add_subdirectory(seatest)
  add_subdirectory(test)
endif()

add_custom_target(run_tests
  COMMAND bash -c "${CMAKE_BINARY_DIR}/target/unit_tests"
)
