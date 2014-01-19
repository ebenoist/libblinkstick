lib blinkstick
=============

A [blinkstick](http://www.blinkstick.com/) library in C.

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

## Known Issues
- Cannot turn off or set a color to 0.
