libBlinkStick
=============

A [blinkstick](http://www.blinkstick.com/) library in C with few dependencies.

## Requirements
- libusb, ```brew install libusb``` on Mac OS X
- clang
- cmake ```brew install cmake```

## Running tests
- ```script/test```

## To build the test app
- Edit the make file to point at your install of libusb. *Note:* Will be replaced soon with a proper configure script.
- ```script/build``` or ```script/build --disable-tests``` to disable the unit tests.
- ```./target/blinkstick --color 255 0 0```

## Warning
This is largely a work in progress. Expect nothing to work, things to change, etc...

## Example

```C
#include <libblinkstick.h>

int main() {
  blinkstick_device *device = find_blinkstick();
  rgb_color *red = rgb_color_factory(255,0,0);
  set_color(color, device);

  destroy_color(color);
  destroy_blinkstick(device);

  return 0;
}
```
