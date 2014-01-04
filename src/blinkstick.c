#include <stdio.h>
#include <libusb.h>

void print_device(libusb_device *device, int i) {
  struct libusb_device_descriptor desc;
  int result = libusb_get_device_descriptor(device, &desc);

  printf("Device: %d\n", i);
  printf("--------------\n");
  if (result >= 0) {
    printf("%04x:%04x (bus %d, device %d)\n",
        desc.idVendor, desc.idProduct,
        libusb_get_bus_number(device), libusb_get_device_address(device));
  } else {
    printf("Failed to read\n");
  }
  printf("--------------\n\n");
}

int main() {
  libusb_device **devices;
  libusb_context *context = NULL;

  int result;
  ssize_t device_count;

  printf("Initializing USB context\n");
  result = libusb_init(&context);
  // libusb_set_debug(context, 3);
  device_count = libusb_get_device_list(context, &devices);

  printf("%d devices found\n", (int)device_count);

  for(int i = 0; i < device_count; i++) {
    libusb_device *device = devices[i];
    print_device(device, i);
  }

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
