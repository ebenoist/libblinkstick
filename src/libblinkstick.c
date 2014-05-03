#include "libblinkstick.h"

bool print_debug = false;

void debug(const char *fmt, ...) {
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

int is_product_and_vendor_id(int vendor_id, int product_id) {
  return ((vendor_id == BLINKSTICK_VENDOR_ID) && (product_id == BLINKSTICK_PRODUCT_ID));
}

int is_blinkstick(libusb_device *device) {
  struct libusb_device_descriptor desc;
  int result = libusb_get_device_descriptor(device, &desc);

  if (result >= 0) {
    if (is_product_and_vendor_id(desc.idVendor, desc.idProduct)) {
      debug("Found the blinkstick\n");

      return true; // Will only find the first. TODO: find more.
    }
  }

  return false;
}

libusb_device_handle* claim_device(libusb_device* device) {
  if (device == NULL) {
    debug("No device to claim\n");
    return NULL;
  }

  libusb_device_handle *dev_handle = NULL;
  int open_device_result;

  open_device_result = libusb_open(device, &dev_handle);

  if (open_device_result >= 0) {
    libusb_claim_interface(dev_handle, 0);
    libusb_ref_device(device);
  } else {
    debug("Failed at claiming device\n");
  }

  return dev_handle;
}

blinkstick_device* find_blinkstick() {
  libusb_device **devices;
  libusb_context *context = NULL;

  ssize_t device_count;
  debug("Initializing USB context");

  libusb_init(&context);
  if (print_debug) {
    libusb_set_debug(context, 3);
  }

  device_count = libusb_get_device_list(context, &devices);
  debug("Found %d usb devices.", device_count);
  libusb_device *blinkstick = NULL;

  for(int i = 0; i < device_count; i++) {
    libusb_device *device = devices[i];

    if(is_blinkstick(device)) {
      blinkstick = device;
    }
  }

  libusb_device_handle *dev_handle = claim_device(blinkstick);
  libusb_free_device_list(devices, 1);

  return blinkstick_factory(dev_handle, context);
}

void set_color(rgb_color *color, blinkstick_device *blinkstick) {
  unsigned char *color_to_transfer = color->bytes;
  libusb_control_transfer(blinkstick->handle, 0x20, 0x9, 0x1, 0x0000, color_to_transfer, COLOR_PACKET_SIZE, 2);
}

void off(blinkstick_device *blinkstick) {
  rgb_color *off = rgb_color_factory(0,0,0);
  set_color(off, blinkstick);
  destroy_color(off);
}

void destroy_blinkstick(blinkstick_device *device) {
  libusb_close(device->handle);
  libusb_exit(device->usb_context);
  free(device);
}

blinkstick_device* blinkstick_factory(libusb_device_handle *handle, libusb_context *context) {
  blinkstick_device *device = malloc(sizeof(blinkstick_factory));
  device->handle = handle;
  device->usb_context = context;
  return device;
}

// RGB
rgb_color* rgb_color_factory(int red, int green, int blue) {
  rgb_color *color = malloc(sizeof(rgb_color));

  color->red = red;
  color->green = green;
  color->blue = blue;
  color->bytes = rgb_to_char(color);

  return color;
}

unsigned char * rgb_to_char(rgb_color *color) {
  unsigned char* bytes = malloc(sizeof(unsigned char[4]));
  bytes[0] = '\x01';
  bytes[1] = (color->red & 0xff);
  bytes[2] = (color->green & 0xff);
  bytes[3] = (color->blue & 0xff);

  return bytes;
}

void destroy_color(rgb_color *color) {
  free(color->bytes);
  free(color);
}

