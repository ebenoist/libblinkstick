#pragma once

#include <hidapi.h>
#include <stdbool.h>

#ifdef _WIN32
#ifdef libblinkstick_EXPORTS
#define BLINKSTICK_API __declspec(dllexport)
#else
#define BLINKSTICK_API
#endif
#else
#define BLINKSTICK_API
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @file libblinkstick.h
 * @brief Header for libblinkstick
 *
 * libblinkstick is meant to to be a simple library for talking to a blinkstick.
 * The BlinkStick Square, BlinkStick v1.1, and the BlinkStick Pro are officially
 * supported and it's likely that other devices work as well.
 *
 * libblinkstick depends on hidapi for interacting with the USB devices, but
 * otherwise has no other dependencies.
 *
 * Included are functions to turn on and off any of the LEDs and change their
 * color via an rgb color. Multiple devices are supported.
 */
static int const BLINKSTICK_VENDOR_ID = 8352;    //"0X20A0";
static int const BLINKSTICK_PRODUCT_ID = 16869;  //"0X41E5";

static int const BLINKSTICK_MODE_MSG_SIZE = 2;
static int const BLINKSTICK_SINGLE_LED_MSG_SIZE = 4;
static int const BLINKSTICK_INDEXED_LED_MSG_PACKET_SIZE = 6;

/**
 * @brief A blinkstick_device holds a pointer to the hid device
 * and is used when setting colors, modes, or turning the device
 * off.
 * @details Construct this device by using blinkstick_find and
 * free it with blinkstick_destroy. Example:
 * @code
 * blinkstick_device* device = blinkstick_find();
 * // destroy
 * blinkstick_destroy(device);
 * @endcode
 */
typedef struct blinkstick_device {
  hid_device* handle;
} blinkstick_device;

// Struct for storing an RGB color value
typedef struct {
  unsigned char red;    // Red component (0-255)
  unsigned char green;  // Green component (0-255)
  unsigned char blue;   // Blue component (0-255)
} blinkstick_color;

/**
 * @brief Possible blink stick modes (only valid for Blinkstick Pro).
 */
typedef enum blinkstick_mode {
  UNKNOWN_MODE = -1,    // Unknown mode
  NORMAL_MODE = 0,      // Normal (non-inverse) LED control
  INVERSE_MODE = 1,     // Inverse LED control
  SMART_PIXEL_MODE = 2  // Smart pixel (WS2812) LED control
} blinkstick_mode;

/**
 * @brief Find the first blinkstick device on the bus registered
 * with HID.
 * @details Note the caller is responsible for deleting the instance of
 * the blinkstick_device using blinkstick_destroy.
 * @return pointer to a blinkstick_device.
 */
BLINKSTICK_API blinkstick_device* blinkstick_find();

/**
 * @brief Given a count will return a pointer array of blinkstick
 * devices. This will abort if the number found is less than
 * the given count.
 * @param count the number of blinkstick devices to find.
 * @return an array of blinkstick device pointers.
 */
BLINKSTICK_API blinkstick_device** blinkstick_find_many(const int count);

/**
 * @brief Sets the LED at the given index and channel to the specified color for
 * the provided device.
 * @param blinkstick pointer to the blinkstick_device to modify.
 * @param channel the channel to set the LED color on.
 * @param index which LED to set the color of.
 * @param red the red component of the new color.
 * @param green the green component of the new color.
 * @param blue the blue component of the new color.
 */
BLINKSTICK_API bool blinkstick_set_color(blinkstick_device* blinkstick,
                                         const int channel,
                                         const int index,
                                         const int red,
                                         const int green,
                                         const int blue);

/**
 * @brief Reads the color from the blinkstick at a given index.
 * @param blinkstick pointer to the blinckstick_device to read from.
 * @param index the index of the LED to read from.
 * @return pointer to a blinkstick_color struct containing the read color.
 */
BLINKSTICK_API blinkstick_color* blinkstick_get_color(
    struct blinkstick_device* blinkstick,
    const int index);

/**
 * @brief Set the mode of the blinkstick.
 * @details Possible modes are "normal" (non-inverse LED control),
 * "inverse" (LED values are inverted) and "smart" (LEDs are WS2812 smart LEDs).
 * Note that you'll need to implement a delay after setting the mode before
 * setting the color on the blinkstick device.
 */
BLINKSTICK_API bool blinkstick_set_mode(blinkstick_device* blinkstick,
                                        enum blinkstick_mode mode);

/**
 * @brief Read the mode currently set on the blinkstick.
 * @param blinkstick pointer to the blinkstick device.
 * @return the current mode.
 */
BLINKSTICK_API enum blinkstick_mode blinkstick_get_mode(
    blinkstick_device* blinkstick);

/**
 * @brief Turns off the led at the specified index for the provided device.
 * This is the same as using set_color with the RGB value (0, 0, 0)
 */
BLINKSTICK_API bool blinkstick_off(blinkstick_device* blinkstick,
                                   const int channel,
                                   const int index);

/**
 * @brief Turns on debug logging.
 */
BLINKSTICK_API void blinkstick_debug();

/**
 * @brief Frees the given blinkstick device
 * @param device the device to free.
 */
BLINKSTICK_API void blinkstick_destroy(blinkstick_device* device);

#ifdef __cplusplus
}
#endif
