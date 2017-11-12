#include <hidapi/hidapi.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

/**
 * @file libblinkstick.h
 * @brief Header for libBlinkStick
 *
 * libBlinkStick is meant to to be a simple library for talking to a blinkstick
 * Both the blinkstick square and blinkstick v1.1 are officially supported and
 * it's likely that other devices work as well.
 *
 * libBlinkStick depends on hidapi for interacting with the USB devices, but
 * otherwise has no other dependencies.
 *
 * Included are functions to turn on and off any of the LEDs and change their
 * color via an rgb color. Multiple devices are supported.
 */

static int const BLINKSTICK_VENDOR_ID = 8352;    //"0X20A0";
static int const BLINKSTICK_PRODUCT_ID = 16869;  //"0X41E5";

static int const BLINKSTICK_SINGLE_LED_MSG_SIZE = 4;
static int const BLINKSTICK_INDEXED_LED_MSG_PACKET_SIZE = 6;

/**
 * A blinkstick_device holds a pointer to the hid device
 * and is used when setting colors, modes, or turning the device
 * off. Construct this device by using blinkstick_find and
 * free it with blinkstick_destroy.
 */
typedef struct blinkstick_device { hid_device* handle; } blinkstick_device;

/**
 * Given a count will return a pointer array of blinkstick
 * devices. This will abort if the number found is less than
 * the given count.
 */
blinkstick_device** blinkstick_find_many(int count);

/**
 * Find the first blinkstick device on the bus registered
 * with HID.
 */
blinkstick_device* blinkstick_find();

/**
 * Sets the LED at the given index to the specified color for the
 * provided device
 */
void blinkstick_set_color(blinkstick_device* device,
                          int index,
                          int red,
                          int green,
                          int blue);

/**
 * Turns off the led at the specified index for the provided device.
 *
 * This is the same as using set_color with the RGB value (0, 0, 0)
 */
void blinkstick_off(blinkstick_device* device, int index);

// Turns on debug logging.
void blinkstick_debug();

/**
 * Frees the given blinkstick device
 */
void blinkstick_destroy(blinkstick_device* device);
