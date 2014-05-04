include_directories(${COMMON_INCLUDES})

# LIBRARY
add_library(libblinkstick libblinkstick.c)
target_link_libraries(libblinkstick ${LIBUSB_LIBRARIES})

# CLI TOOL
add_executable(blinkstick blinkstick.c)
target_link_libraries (blinkstick libblinkstick)
