#include "libblinkstick.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

bool print_debug = false;

#if _WINDOWS
#pragma warning(disable:4996)
#endif

void debug(const char* fmt, ...) {
  if (print_debug) {
    char buffer[256];
    va_list ap;
    va_start(ap, fmt);
    vsprintf(buffer, fmt, ap);
    va_end(ap);

    puts(buffer);
  }
}

void blinkstick_debug() {
  print_debug = true;
  debug("STARTING LIBBLINKSTICK WITH DEBUG LOGGING");
}

unsigned char* rgb_to_char(int red, int green, int blue) {
  unsigned char* bytes = malloc(sizeof(unsigned char[3]));
  bytes[0] = (red & 0xff);
  bytes[1] = (green & 0xff);
  bytes[2] = (blue & 0xff);

  return bytes;
}

blinkstick_device* blinkstick_factory(hid_device* handle) {
  blinkstick_device* device = malloc(sizeof(blinkstick_device));
  device->handle = handle;
  return device;
}

blinkstick_device** blinkstick_find_many(const int count) {
  blinkstick_device** devices = malloc(sizeof(blinkstick_device*) * count);
  // initialize the devices
  for (int i = 0; i < count; i++)
  {
	  devices[i] = blinkstick_factory(NULL);
  }

  debug("initializing usb context");
  const int res = hid_init();
  if (res != 0) {
    debug("failed to initialize hid");
	return devices;
  }

  struct hid_device_info * device_info = 
	  hid_enumerate(BLINKSTICK_VENDOR_ID, BLINKSTICK_PRODUCT_ID);
  if (device_info == NULL)
  {
	  return devices;
  }
  
  devices[0]->handle = hid_open_path(device_info->path);
  debug("found device: %s", device_info->path);

  int num = 1;
  while ((device_info = device_info->next)) {
    devices[num]->handle = hid_open_path(device_info->path);
    debug("found device: %s", device_info->path);
    num++;
  }

  if (count > num) {
    debug("did not find the number of devices wanted: %d, but found %d\n",
           count, num);
  }

  return devices;
}

blinkstick_device* blinkstick_find() {
  return blinkstick_find_many(1)[0];
}

unsigned char* build_control_message(const int index, const int channel, unsigned char* color, size_t* msg_size) {
  if (!msg_size)
  {
    return NULL;
  }
	// Write to the first LED present
	// this will be the _only_ led for the original blinkstick
    if (index == 0 && channel == 0)
    {
	    unsigned char* msg =
		    malloc(sizeof(unsigned char) * BLINKSTICK_SINGLE_LED_MSG_SIZE);
	    *msg_size = BLINKSTICK_SINGLE_LED_MSG_SIZE;
	    msg[0] = 0x1;
	    msg[1] = color[0];
	    msg[2] = color[1];
	    msg[3] = color[2];
	    return msg;
    }

	// Writing to the other LEDs requires a different payload
	// this changes the write mode (first two bytes) and then
	// assigns the index.
    unsigned char* msg =
	    malloc(sizeof(unsigned char) * BLINKSTICK_INDEXED_LED_MSG_PACKET_SIZE);
    *msg_size = BLINKSTICK_INDEXED_LED_MSG_PACKET_SIZE;
    msg[0] = 0x5;
    msg[1] = channel;
    msg[2] = index;
    msg[3] = color[0];
    msg[4] = color[1];
    msg[5] = color[2];
    return msg;
}

unsigned char* build_mode_message(const int mode) {
	unsigned char* msg =
		malloc(sizeof(unsigned char) * BLINKSTICK_MODE_MSG_SIZE);
	msg[0] = 0x0004;
	msg[1] = mode;
	return msg;
}

bool is_null(blinkstick_device* blinkstick)
{
	return blinkstick->handle == NULL;
}

bool blinkstick_set_mode(blinkstick_device* blinkstick, const enum blinkstick_mode mode) {
	unsigned char* msg = build_mode_message(mode);
	if (is_null(blinkstick))
	{
		debug("input hid handle is null.");
		return false;
	}
	const int result = hid_send_feature_report(blinkstick->handle, msg, sizeof(msg));
	if (result == -1)
	{
		debug("error writing mode to device!");
		return false;
	}
	free(msg);
	return true;
}

enum blinkstick_mode blinkstick_get_mode(blinkstick_device *blinkstick)
{
	unsigned char* data = malloc(sizeof(unsigned char) * 2);
	data[0] = 0x0004;
	const int result = hid_get_feature_report(blinkstick->handle, data, 2);
	if (result == -1)
	{
		debug("error reading mode from device.");
		return unknown;
	}

    const enum blinkstick_mode return_mode = data[1];
	free(data); // cleanup
	return return_mode;
}


bool blinkstick_set_color(blinkstick_device* blinkstick,
                          const int channel,
                          const int index,
                          const int red,
                          const int green,
                          const int blue) {
	if (is_null(blinkstick))
	{
		debug("input hid handle is null.");
		return false;
	}
	unsigned char* color = rgb_to_char(red, green, blue);
	size_t msg_size = 0;
	unsigned char* msg = build_control_message(index, channel, color, &msg_size);
	const int result = hid_send_feature_report(blinkstick->handle, msg, msg_size);
	if (result == -1)
	{
		debug("error writing color to device!");
		return false;
	}
	free(msg);
	free(color);
	return true;
}

int determine_report_id(const int count, int* max_leds)
{
	int report_id = 9;

	if (count <= 8 *3)
	{
		*max_leds = 8;
		report_id = 6;
	}
	else if (count <= 16 * 3)
	{
		*max_leds = 16;
		report_id = 7;
	}
	else if (count <= 32 * 3)
	{
		*max_leds = 32;
		report_id = 8;
	}
	else if (count <= 64 * 3)
	{
		*max_leds = 64;
		report_id = 9;
	}

	return report_id;
}

blinkstick_color* blinkstick_get_color(struct blinkstick_device* blinkstick, const int index)
{
	blinkstick_color *color = malloc(sizeof(blinkstick_color));
	color->red = 0;
	color->green = 0;
	color->blue = 0;

	if (index == 0)
	{
		unsigned char* data = malloc(sizeof(unsigned char) * 33);
		data[0] = 0x0001;
		const int result = hid_get_feature_report(blinkstick->handle,
			data,
			33);
		if (result == -1)
		{
			debug("unable to read color from blinkstick");
		}
		else
		{
			color->red = data[1];
			color->green = data[2];
			color->blue = data[3];
		}
        // free memory
		free(data);
	}
	else
	{
	    const int count = (index + 1) * 3;
		int max_leds;
	    const int report_id = determine_report_id(count, &max_leds);

		unsigned char* data = malloc(sizeof(unsigned char) *
			max_leds * 3 + 2);
		data[0] = report_id;

		const int result = hid_get_feature_report(blinkstick->handle,
			data,
			max_leds * 3 + 2);

		if (result == -1)
		{
			debug("unable to read color from blinkstick.");
		}
		else
		{
			color->red = data[index * 3 + 3];
			color->green = data[index * 3 + 2];
			color->blue = data[index * 3 + 4];
		}
		// free memory
		free(data);
	}
	return color;
}


bool blinkstick_off(blinkstick_device* blinkstick, const int channel, const int index) {
  return blinkstick_set_color(blinkstick, channel, index, 0, 0, 0);
}

void blinkstick_destroy(blinkstick_device* device) {
  hid_close(device->handle);
  free(device);
}
