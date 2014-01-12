lib blinkstick
=============

A [blinkstick](http://www.blinkstick.com/) library in C.

## Example

```C
#include <libblinkstick.h>

int main() {
  blinkstick_device *device = find_blinkstick();
  set_color("FF9900", device);

  free(device);

  return 0;
}
```
