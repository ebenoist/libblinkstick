#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <libusb.h>
#include <stdlib.h>

static int const BLINKSTICK_VENDOR_ID = 8352; //"0X20A0";
static int const BLINKSTICK_PRODUCT_ID = 16869; //"0X41E5";

struct blinkstick_device;
typedef struct blinkstick_device blinkstick_device;

void set_debug_true();
blinkstick_device* find_blinkstick();
void set_color(char *color, blinkstick_device *device);

