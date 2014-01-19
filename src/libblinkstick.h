#include <libusb.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rgb.h"

static int const BLINKSTICK_VENDOR_ID = 8352; //"0X20A0";
static int const BLINKSTICK_PRODUCT_ID = 16869; //"0X41E5";
static int const COLOR_PACKET_SIZE = 4;

struct blinkstick_device;
typedef struct blinkstick_device blinkstick_device;

struct blinkstick_device {
  libusb_device_handle* handle;
  libusb_context* usb_context;
};

void set_debug_true();
blinkstick_device* find_blinkstick();
void set_color(rgb_color *color, blinkstick_device *device);
void off(blinkstick_device *device);
void destroy_blinkstick(blinkstick_device *device);
