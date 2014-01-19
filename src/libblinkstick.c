#include "libblinkstick.h"

bool print_debug = false;

void debug(char * str) {
  if (print_debug) {
    printf("%s\n", str);
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
  debug("Initializing USB context\n");

  libusb_init(&context);
  if (print_debug) {
    libusb_set_debug(context, 3);
  }

  device_count = libusb_get_device_list(context, &devices);
  libusb_device *blinkstick = NULL;

  for(int i = 0; i < device_count; i++) {
    libusb_device *device = devices[i];

    if(is_blinkstick(device)) {
      blinkstick = device;
    }
  }

  libusb_device_handle *dev_handle = claim_device(blinkstick);

  libusb_free_device_list(devices, 1);

  blinkstick_device *ret = (blinkstick_device*)malloc(sizeof(blinkstick_device));
  ret->handle = dev_handle;
  ret->usb_context = context;

  return ret;
}

void set_color(rgb_color *color, blinkstick_device *blinkstick) {
  unsigned char *color_to_transfer = color->bytes;
  libusb_control_transfer(blinkstick->handle, 0x20, 0x9, 0x1, 0x0000, color_to_transfer, COLOR_PACKET_SIZE, 2);
}

void off(blinkstick_device *blinkstick) {
  set_color(rgb_color_factory(0,0,0), blinkstick);
}

void destroy_blinkstick(blinkstick_device *device) {
  libusb_close(device->handle);
  libusb_exit(device->usb_context);
  free(device);
}

