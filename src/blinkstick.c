#include <stdio.h>
#include <libusb.h>

int main() {
  libusb_device **devices;
  libusb_context *context = NULL;

  int result;
  ssize_t device_count;

  result = libusb_init(&context);
  libusb_set_debug(context, 3);
  device_count = libusb_get_device_list(context, &devices);

  printf("%d was the result.", result);
  printf("%d devices found\n", (int)device_count);

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
