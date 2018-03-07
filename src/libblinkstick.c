#include "libblinkstick.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

bool print_debug = false;

void debug(const char* fmt, ...) {
  if (print_debug) {
    char buffer[256];
    va_list ap;
    va_start(ap, fmt);
    vsprintf(buffer, fmt, ap);
    va_end(ap);

    puts(buffer);
  }
}

void blinkstick_debug() {
  print_debug = true;
  debug("STARTING LIBBLINKSTICK WITH DEBUG LOGGING");
}

unsigned char* rgb_to_char(int red, int green, int blue) {
  unsigned char* bytes = malloc(sizeof(unsigned char[3]));
  bytes[0] = (red & 0xff);
  bytes[1] = (green & 0xff);
  bytes[2] = (blue & 0xff);

  return bytes;
}

blinkstick_device* blinkstick_factory(hid_device* handle) {
  blinkstick_device* device = malloc(sizeof(blinkstick_device));
  device->handle = handle;
  return device;
}

blinkstick_device** blinkstick_find_many(int count) {
  blinkstick_device** devices = malloc(sizeof(blinkstick_device*) * count);

  debug("initializing usb context");
  int res = hid_init();
  if (res != 0) {
    debug("failed to initialize hid");
    exit(1);
  }

  struct hid_device_info* device_info;
  device_info = hid_enumerate(BLINKSTICK_VENDOR_ID, BLINKSTICK_PRODUCT_ID);
  devices[0] = blinkstick_factory(hid_open_path(device_info->path));
  debug("found device: %s", device_info->path);

  int num = 1;
  while ((device_info = device_info->next)) {
    devices[num] = blinkstick_factory(hid_open_path(device_info->path));
    debug("found device: %s", device_info->path);
    num++;
  }

  if (count > num) {
    printf("did not find the number of devices wanted: %d, but found %d\n",
           count, num);
    exit(1);
  }

  return devices;
}

blinkstick_device* blinkstick_find() {
  return blinkstick_find_many(1)[0];
}

unsigned char* build_control_message(int index, unsigned char* color) {
  // Write to the first LED present
  // this will be the _only_ led for the original blinkstick
  if (index == 0) {
    unsigned char* msg =
        malloc(sizeof(unsigned char) * BLINKSTICK_SINGLE_LED_MSG_SIZE);
    msg[0] = 0x1;
    msg[1] = color[0];
    msg[2] = color[1];
    msg[3] = color[2];
    return msg;
  }

  // Writing to the other LEDs requires a different payload
  // this changes the write mode (first two bytes) and then
  // assigns the index.
  unsigned char* msg =
      malloc(sizeof(unsigned char) * BLINKSTICK_INDEXED_LED_MSG_PACKET_SIZE);
  msg[0] = 0x0005;
  msg[1] = 0x05;
  msg[2] = index;
  msg[3] = color[0];
  msg[4] = color[1];
  msg[5] = color[2];

  return msg;
}

void blinkstick_set_color(blinkstick_device* blinkstick,
                          int index,
                          int red,
                          int green,
                          int blue) {
  unsigned char* color = rgb_to_char(red, green, blue);
  unsigned char* msg = build_control_message(index, color);

  hid_write(blinkstick->handle, msg, sizeof(msg));
  free(msg);
  free(color);
}

void blinkstick_off(blinkstick_device* blinkstick, int index) {
  blinkstick_set_color(blinkstick, index, 0, 0, 0);
}

void blinkstick_destroy(blinkstick_device* device) {
  hid_close(device->handle);
  free(device);
}
