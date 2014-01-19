libBlinkStick
=============

A [blinkstick](http://www.blinkstick.com/) library in C with few dependencies.

## Requirements
- libusb, ```brew install libusb``` on Mac OS X
- Standard build tools (ie. make, gcc, etc...)

## To build the test app 
- Edit the make file to point at your install of libusb. *Note:* Will be replaced soon with a proper configure script.

```
LFLAGS = -L/usr/local/Cellar/libusb/1.0.9/lib/
INCLUDES = -I/usr/local/include/libusb-1.0/
```
- ```make```
- ```./blinkstick.app --color 255 1 1```

## Warning
This is largely a work in progress. Expect nothing to work, things to change, etc...

## Example

```C
#include <libblinkstick.h>

int main() {
  blinkstick_device *device = find_blinkstick();
  rgb_color *red = rgb_color_factory(255,1,1);
  set_color(color, device);

  free(color);
  free(device);

  return 0;
}
```
