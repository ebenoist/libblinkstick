# LIBRARY
add_library(libblinkstick libblinkstick.c libblinkstick.h)
target_include_directories(libblinkstick
        PUBLIC
          ${CMAKE_CURRENT_SOURCE_DIR}
          ${HID_INCLUDE_DIRS})
target_link_libraries(libblinkstick PUBLIC ${HIDAPI_LIBRARIES})
set_target_properties(libblinkstick PROPERTIES OUTPUT_NAME blinkstick)
set_property(TARGET libblinkstick PROPERTY C_STANDARD 11)

install(TARGETS libblinkstick
        RUNTIME DESTINATION "${INSTALL_BIN_DIR}"
        ARCHIVE DESTINATION "${INSTALL_LIB_DIR}"
        LIBRARY DESTINATION "${INSTALL_LIB_DIR}")

install(FILES libblinkstick.h DESTINATION "${INSTALL_INC_DIR}")

if(BUILD_CLI)
    # CLI TOOL
    add_executable(blinkstick blinkstick.c)
    add_dependencies(blinkstick libblinkstick)
    target_link_libraries(blinkstick PUBLIC libblinkstick)

    install(TARGETS blinkstick
            RUNTIME DESTINATION "${INSTALL_BIN_DIR}"
            ARCHIVE DESTINATION "${INSTALL_LIB_DIR}"
            LIBRARY DESTINATION "${INSTALL_LIB_DIR}")
endif(BUILD_CLI)
