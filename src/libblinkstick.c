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
  debug("Initializing USB context");
  blinkstick_device** devices = malloc(sizeof(blinkstick_device*) * count);

  int res;
  res = hid_init();

  if (res != 0) {
    debug("failed to initialize hid");
  }

  struct hid_device_info* device_info;
  device_info = hid_enumerate(BLINKSTICK_VENDOR_ID, BLINKSTICK_PRODUCT_ID);
  devices[0] = blinkstick_factory(hid_open_path(device_info->path));

  int num = 1;
  while ((device_info = device_info->next)) {
    devices[num] = blinkstick_factory(hid_open_path(device_info->path));
    num++;
  }

  return devices;
}

void set_color(int index, rgb_color* color, blinkstick_device* blinkstick) {
  if (index == 0) {
    unsigned char out[4] = {0x1, color->bytes[0], color->bytes[1],
                            color->bytes[2]};
    hid_write(blinkstick->handle, out, sizeof(out));

  } else {
    unsigned char out[6] = {
        0x0005, 0x05, index, color->bytes[0], color->bytes[1], color->bytes[2]};
    hid_write(blinkstick->handle, out, sizeof(out));
  }
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

// RGB
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
