add_library(libblinkstick libblinkstick.c libblinkstick.h)
target_include_directories(libblinkstick
        PUBLIC
          $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
          $<INSTALL_INTERFACE:include>)

target_link_libraries(libblinkstick PUBLIC hidapi::hidapi)
set_target_properties(libblinkstick PROPERTIES OUTPUT_NAME blinkstick)
set_property(TARGET libblinkstick PROPERTY C_STANDARD 11)

install(TARGETS libblinkstick EXPORT libblinkstickTargets
        RUNTIME DESTINATION "${INSTALL_BIN_DIR}"
        ARCHIVE DESTINATION "${INSTALL_LIB_DIR}"
        LIBRARY DESTINATION "${INSTALL_LIB_DIR}")

install(FILES libblinkstick.h DESTINATION "${INSTALL_INC_DIR}")

include(CMakePackageConfigHelpers)

write_basic_package_version_file(
        "${CMAKE_BINARY_DIR}/libblinkstick/libblinkstickConfigVersion.cmake"
        VERSION ${libblinkstick_VERSION}
        COMPATIBILITY AnyNewerVersion
)

if(BUILD_CLI)
    # CLI TOOL
    set(cli_tool_name blinkstick-cli)
    add_executable(${cli_tool_name} blinkstick.c)
    add_dependencies(${cli_tool_name} libblinkstick)
    target_link_libraries(${cli_tool_name} PUBLIC libblinkstick)
    set_target_properties(${cli_tool_name} PROPERTIES OUPUT_NAME blinkstick)

    install(TARGETS ${cli_tool_name} EXPORT libblinkstickTargets
            RUNTIME DESTINATION "${INSTALL_BIN_DIR}"
            ARCHIVE DESTINATION "${INSTALL_LIB_DIR}"
            LIBRARY DESTINATION "${INSTALL_LIB_DIR}")
endif(BUILD_CLI)

export(EXPORT 
            libblinkstickTargets 
       FILE 
            "${CMAKE_BINARY_DIR}/libblinkstick/libblinkstickTargets.cmake")

configure_package_config_file(
        ${PROJECT_SOURCE_DIR}/cmake/libblinkstickConfig.cmake.in # input
        ${CMAKE_BINARY_DIR}/libblinkstick/libblinkstickConfig.cmake # output
        INSTALL_DESTINATION ${CMAKE_INSTALL_PREFIX}/cmake)

install(EXPORT 
            libblinkstickTargets
        FILE 
            libblinkstickTargets.cmake
        DESTINATION 
            cmake)

install(FILES
            "${CMAKE_BINARY_DIR}/libblinkstick/libblinkstickConfig.cmake"
            "${CMAKE_BINARY_DIR}/libblinkstick/libblinkstickConfigVersion.cmake"
        DESTINATION
                cmake
        COMPONENT
                Devel)

        