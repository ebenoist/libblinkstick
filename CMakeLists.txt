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

# Have we found libusb?
if(LIBUSB_FOUND)
  message(STATUS "libusb was found: ${LIBUSB_LIBRARIES}")
else(LIBUSB_FOUND)
  message(FATAL_ERROR "Could not find libusb.")
endif(LIBUSB_FOUND)

option(test "Build all tests." OFF)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -stdlib=libc++")

add_subdirectory(src)

if (test)
  add_subdirectory(vendor/gtest-1.7.0)
  add_subdirectory(test)
endif()
