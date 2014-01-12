lib blinkstick
=============

A blinkstick library in C

## Provides the following
```C
struct blinkstick_device;
typedef struct blinkstick_device blinkstick_device;

void set_debug_true();
blinkstick_device* find_blinkstick();
void set_color(char *color, blinkstick_device *device);
```

## Example

```C
#include <libblinkstick.h>

int main(int argc, char **argv) {
  parse_args(argv);
  blinkstick_device *device = find_blinkstick();
  set_color("FF9900", device);

  free(device);
  return 0;
}
```
