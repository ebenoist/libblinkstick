#include "libblinkstick.h"

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

void set_debug_true() {
  print_debug = true;
  debug("STARTING LIBBLINKSTICK WITH DEBUG LOGGING");
}

blinkstick_device** find_blinksticks(int count) {
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

  if (count != num) {
    printf("did not find the number of devices wanted: %d, but found %d\n",
           count, num);
    exit(1);
  }

  return devices;
}

unsigned char* build_control_message(int index, rgb_color* color) {
  // Write to the first LED present
  // this will be the _only_ led for the original blinkstick
  if (index == 0) {
    unsigned char* msg = malloc(sizeof(unsigned char) * SINGLE_LED_MSG_SIZE);
    msg[0] = 0x1;
    msg[1] = color->bytes[0];
    msg[2] = color->bytes[1];
    msg[3] = color->bytes[2];
    return msg;
  }

  // Writing to the other LEDs requires a different payload
  // this changes the write mode (first two bytes) and then
  // assigns the index.
  unsigned char* msg =
      malloc(sizeof(unsigned char) * INDEXED_LED_MSG_PACKET_SIZE);
  msg[0] = 0x0005;
  msg[1] = 0x05;
  msg[2] = index;
  msg[3] = color->bytes[0];
  msg[4] = color->bytes[1];
  msg[5] = color->bytes[2];

  return msg;
}

void set_color(int index, rgb_color* color, blinkstick_device* blinkstick) {
  unsigned char* msg = build_control_message(index, color);
  hid_write(blinkstick->handle, msg, sizeof(msg));
  free(msg);
}

void off(int index, blinkstick_device* blinkstick) {
  rgb_color* off = rgb_color_factory(0, 0, 0);
  set_color(index, off, blinkstick);
  destroy_color(off);
}

void destroy_blinkstick(blinkstick_device* device) {
  hid_close(device->handle);
  free(device);
}

blinkstick_device* blinkstick_factory(hid_device* handle) {
  blinkstick_device* device = malloc(sizeof(blinkstick_device));
  device->handle = handle;
  return device;
}

// RGB functions
rgb_color* rgb_color_factory(int red, int green, int blue) {
  rgb_color* color = malloc(sizeof(rgb_color));

  color->red = red;
  color->green = green;
  color->blue = blue;
  color->bytes = rgb_to_char(color);

  return color;
}

unsigned char* rgb_to_char(rgb_color* color) {
  unsigned char* bytes = malloc(sizeof(unsigned char[3]));
  bytes[0] = (color->red & 0xff);
  bytes[1] = (color->green & 0xff);
  bytes[2] = (color->blue & 0xff);

  return bytes;
}

void destroy_color(rgb_color* color) {
  free(color->bytes);
  free(color);
}
