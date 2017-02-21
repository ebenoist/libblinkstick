cmake_minimum_required (VERSION 2.6)

project (libblinkstick)

enable_testing()

find_package(PkgConfig)
if(PKG_CONFIG_FOUND)
  message(STATUS "PkgConfig was found.")
  pkg_check_modules(LIBUSB REQUIRED libusb-1.0)
else(PKG_CONFIG_FOUND)
  message(FATAL_ERROR "Could not find PkgConfig")
endif(PKG_CONFIG_FOUND)

link_directories(${LIBUSB_LIBRARY_DIRS})

option(test "Build all tests." OFF)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m64 -std=c++0x -stdlib=libc++ -g3 -Wall -O0  -arch x86_64")
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -m64 -arch x86_64")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../target)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../target)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../target)

set(COMMON_INCLUDES ${PROJECT_SOURCE_DIR}/src ${PROJECT_SOURCE_DIR}/vendor/seatest ${LIBUSB_INCLUDE_DIRS})

add_subdirectory(src)

if (test)
  add_subdirectory(vendor/seatest)
  add_subdirectory(test)
endif()



