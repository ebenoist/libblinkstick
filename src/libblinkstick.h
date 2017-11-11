#include <hidapi/hidapi.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

/**
 * Represents an rgb color
 *
 * Constructed of 3 colors, each with a max value
 * of 255 and a byte represenation of the rgb value
 * for sending directly to the blinkstick_device
 */
typedef struct rgb_color {
  int red;
  int green;
  int blue;
  unsigned char* bytes;
} rgb_color;

/**
 * Builds an rgb_color struct, this will malloc a new struct
 * and return a pointer. Ensure that you release it using
 * destroy_color.
 */
rgb_color* rgb_color_factory(int red, int green, int blue);

/**
 * Frees an rgb struct and its byte represenation
 */
void destroy_color(rgb_color* color);

unsigned char* rgb_to_char(rgb_color* color);

static int const BLINKSTICK_VENDOR_ID = 8352;    //"0X20A0";
static int const BLINKSTICK_PRODUCT_ID = 16869;  //"0X41E5";

static int const SINGLE_LED_MSG_SIZE = 4;
static int const INDEXED_LED_MSG_PACKET_SIZE = 6;

/**
 * A blinkstick_device holds a pointer to the hid device
 * and is used when setting colors, modes, or turning the device
 * off. Construct this device by using find_blinksticks and
 * free it with destroy_blinkstick
 */
typedef struct blinkstick_device { hid_device* handle; } blinkstick_device;

/**
 * Given a count will return a pointer array of blinkstick
 * devices.
 */
blinkstick_device** find_blinksticks(int count);

/**
 * Find the first blinkstick device on the bus registered
 * with HID.
 */
blinkstick_device* find_blinkstick();

/**
 * Sets the LED at the given index to the specified color for the
 * provided device
 */
void set_color(int index, rgb_color* color, blinkstick_device* device);

/**
 * Turns off the led at the specified index for the provided device.
 *
 * This is the same as using set_color with the RGB value (0, 0, 0)
 */
void off(int index, blinkstick_device* device);

// Turns on debug logging.
void set_debug_true();

/**
 * Frees the given blinkstick device
 */
void destroy_blinkstick(blinkstick_device* device);

blinkstick_device* blinkstick_factory(hid_device* handle);
