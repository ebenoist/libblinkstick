include_directories(${COMMON_INCLUDES})

# LIBRARY
add_library(libblinkstick libblinkstick.c)
target_link_libraries(libblinkstick ${HIDAPI_LIBRARIES})
set_target_properties(libblinkstick PROPERTIES OUTPUT_NAME blinkstick)

# CLI TOOL
add_executable(blinkstick blinkstick.c)
target_link_libraries(blinkstick libblinkstick)

install(TARGETS blinkstick libblinkstick
        RUNTIME DESTINATION "${INSTALL_BIN_DIR}"
        ARCHIVE DESTINATION "${INSTALL_LIB_DIR}"
        LIBRARY DESTINATION "${INSTALL_LIB_DIR}")

install(FILES libblinkstick.h DESTINATION "${INSTALL_INC_DIR}")
