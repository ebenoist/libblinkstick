include_directories(${LIBUSB_INCLUDE_DIRS})

add_library(libblinkstick libblinkstick.c)
add_executable(blinkstick blinkstick.c)
target_link_libraries (blinkstick libblinkstick)
target_link_libraries(libblinkstick ${LIBUSB_LIBRARIES})
