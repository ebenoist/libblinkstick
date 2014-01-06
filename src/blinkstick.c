#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <libusb.h>

static int const blinkstick_vendor_id = 8352; //"0X20A0";
static int const blinkstick_product_id = 16869; //"0X41E5";

int is_product_and_vendor_id(int vendor_id, int product_id) {
  return ((vendor_id == blinkstick_vendor_id) && (product_id == blinkstick_product_id));
}

int is_blinkstick(libusb_device *device) {
  struct libusb_device_descriptor desc;
  int result = libusb_get_device_descriptor(device, &desc);

  if (result >= 0) {
    if (is_product_and_vendor_id(desc.idVendor, desc.idProduct)) {
      printf("Found the blinkstick\n");

      return true; // Will only find the first. TODO: find more.
    }
  }

  return false;
}

int main(int argc, char **argv) {
  libusb_device **devices;
  libusb_context *context = NULL;

  ssize_t device_count;

  printf("Initializing USB context\n");

  libusb_init(&context);
  libusb_set_debug(context, 3);

  device_count = libusb_get_device_list(context, &devices);

  libusb_device *blinkstick;

  for(int i = 0; i < device_count; i++) {
    libusb_device *device = devices[i];
    if(is_blinkstick(device)) {
      blinkstick = device;
    }
  }

  libusb_device_handle *dev_handle = NULL;
  if (blinkstick) {
    int open_device_result;
    open_device_result = libusb_open(blinkstick, &dev_handle);

    if (open_device_result >= 0) {
      printf("Found and open\n");
    }
  } else {
    printf("Found nothing\n");
  }

  printf("Got here to claim interface");
  libusb_claim_interface(dev_handle, 0);

  /* unsigned char red[] = "\x01\x00\x00\xFF"; */

  printf("Got here");
  printf("Writing color: %s", argv[2]);
  unsigned char *color = NULL;
  strncpy((char*)color, argv[0], 20);
  printf("Writing color: %s", color);

  libusb_control_transfer(dev_handle, 0x20, 0x9, 0x1, 0x0000, color, 16, 0);

  libusb_free_device_list(devices, 1);
  libusb_exit(context);

  return 0;
}


/*
 * http://www.dreamincode.net/forums/topic/148707-introduction-to-using-libusb-10/
 *
 * Plans:
 *  * Provide an interface to each blinkstick
 *  * Provide a series of functions to turn on/off and set color.
 *
 * Questions: Should each blinkstick be a struct that responds to a series of commands?
 *  OO vs functional approach?
 *
 *  struct blinkstick {
 *    libusb_device *dev;
 *
 *    function blah() {
 *      send_command(0x0x0x, *dev);
 *    }
 *  }
 */
