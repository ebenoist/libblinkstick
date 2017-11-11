#include "hidapi/hidapi.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

struct rgb_color;
typedef struct rgb_color rgb_color;

struct rgb_color {
  int red;
  int green;
  int blue;
  unsigned char* bytes;
};

rgb_color* rgb_color_factory(int red, int green, int blue);
unsigned char* rgb_to_char(rgb_color* color);
void destroy_color(rgb_color* color);

static int const BLINKSTICK_VENDOR_ID = 8352;    //"0X20A0";
static int const BLINKSTICK_PRODUCT_ID = 16869;  //"0X41E5";
static int const COLOR_PACKET_SIZE = 6;

struct blinkstick_device;
typedef struct blinkstick_device blinkstick_device;

struct blinkstick_device {
  hid_device* handle;
};

// PUBLIC
void set_debug_true();
blinkstick_device** find_blinksticks(int count);
void set_color(int index, rgb_color* color, blinkstick_device* device);
void off(int index, blinkstick_device* device);

// PRIVATE
void destroy_blinkstick(blinkstick_device* device);
blinkstick_device* blinkstick_factory(hid_device* handle);

typedef struct arguments arguments;
struct arguments;

struct arguments {
  rgb_color* color;
  int count;
};
