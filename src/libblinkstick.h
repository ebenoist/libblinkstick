#include <libusb.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rgb.h"

static int const BLINKSTICK_VENDOR_ID = 8352; //"0X20A0";
static int const BLINKSTICK_PRODUCT_ID = 16869; //"0X41E5";

struct blinkstick_device;
typedef struct blinkstick_device blinkstick_device;

struct blinkstick_device {
  libusb_device_handle * handle;
};

void set_debug_true();
blinkstick_device* find_blinkstick();
void set_color(rgb_color *color, blinkstick_device *device);
void off(blinkstick_device *device);
// @handle.control_transfer(:bmRequestType => 0x20, :bRequest => 0x9, :wValue => 0x1, :wIndex => 0x0000, :dataOut => 1.chr + value.red.to_i.chr + value.green.to_i.chr + value.blue.to_i.chr)

