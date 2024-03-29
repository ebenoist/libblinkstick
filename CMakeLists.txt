cmake_minimum_required (VERSION 2.8.12)

project (libblinkstick LANGUAGES C)

option(BUILD_DOCS "Build documentation" ON)
option(BUILD_CLI "Build command line BlinkStick control program" ON)

if(WIN32)
  find_package(hidapi CONFIG REQUIRED)
else(WIN32)
  list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
  find_package(HIDAPI REQUIRED)
  find_package(PkgConfig REQUIRED)
  pkg_search_module(HIDAPI REQUIRED hidapi)
endif(WIN32)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/target)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/target)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/target)

if(BUILD_DOCS)
  find_package(Doxygen)
  if (DOXYGEN_FOUND)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
    message("Doxygen found, setting build rules")

    add_custom_target(docs
    ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Generating API documentation with Doxygen" VERBATIM
    )
  else()
    message("Doxygen needs to be installed to generate the doxygen documentation")
  endif (DOXYGEN_FOUND)
endif(BUILD_DOCS)


set(INSTALL_BIN_DIR "${CMAKE_INSTALL_PREFIX}/bin" CACHE PATH "Installation directory for executables")
set(INSTALL_LIB_DIR "${CMAKE_INSTALL_PREFIX}/lib" CACHE PATH "Installation directory for libraries")
set(INSTALL_INC_DIR "${CMAKE_INSTALL_PREFIX}/include" CACHE PATH "Installation directory for headers")
set(INSTALL_MAN_DIR "${CMAKE_INSTALL_PREFIX}/share/man" CACHE PATH "Installation directory for manual pages")
set(INSTALL_PKGCONFIG_DIR "${CMAKE_INSTALL_PREFIX}/share/pkgconfig" CACHE PATH "Installation directory for pkgconfig (.pc) files")

configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/libblinkstick.pc.in
    ${CMAKE_BINARY_DIR}/libblinkstick.pc @ONLY)

install(FILES ${CMAKE_BINARY_DIR}/libblinkstick.pc DESTINATION "${INSTALL_PKGCONFIG_DIR}")

set(libblinkstick_VERSION_MAJOR 1)
set(libblinkstick_VERSION_MINOR 0)
set(libblinkstick_VERSION_PATCH 0)

set(libblinkstick_VERSION "${libblinkstick_VERSION_MAJOR}.${libblinkstick_VERSION_MINOR}.${libblinkstick_VERSION_PATCH}")
add_subdirectory(src)
