cmake_minimum_required (VERSION 2.6)

project (libblinkstick)

enable_testing()
option(BUILD_DOC "Build documentation" ON)

find_package(PkgConfig REQUIRED)
pkg_search_module(HIDAPI REQUIRED hidapi)

link_libraries(${HIDAPI_LIBRARIES})
include_directories(PUBLIC ${HIDAPI_INCLUDE_DIRS})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/target)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/target)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/target)

set(COMMON_INCLUDES ${PROJECT_SOURCE_DIR}/src ${PROJECT_SOURCE_DIR}/seatest ${HIDAPI_INCLUDE_DIRS})

find_package(Doxygen)
if (DOXYGEN_FOUND)
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
  message("Doxygen build started")

  add_custom_target(docs
  ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  COMMENT "Generating API documentation with Doxygen" VERBATIM
  )
else (DOXYGEN_FOUND)
  message("Doxygen need to be installed to generate the doxygen documentation")
endif (DOXYGEN_FOUND)

add_subdirectory(src)

if (test)
  add_subdirectory(seatest)
  add_subdirectory(test)
endif()

add_custom_target(run_tests
  COMMAND bash -c "${CMAKE_BINARY_DIR}/target/unit_tests"
)
