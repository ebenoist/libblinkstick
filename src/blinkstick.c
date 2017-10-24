#include "libblinkstick.h"
#include <unistd.h>

rgb_color* parse_args(char **flags) {
  rgb_color *color = NULL;

  for (int i = 1; i < sizeof(flags); i++) {
    if(flags[i] != NULL) {
      if (strcmp(flags[i], "--debug") == 0) {
        set_debug_true();
      }

      if (strcmp(flags[i], "--color") == 0) {
        char *red, *green, *blue;

        // sloppy
        red = *(flags + i + 1);
        green = *(flags + i + 2);
        blue = *(flags + i + 3);

        color = rgb_color_factory(atoi(red), atoi(green), atoi(blue));
      }
    }
  }

  return color;
}

int main(int argc, char **argv) {
  rgb_color *color = parse_args(argv);
  blinkstick_device *device = find_blinkstick();

  int i;

  if (device) {
    for(i = 0; i < 8; i++)
    {
      set_color(i, color, device);
      usleep(1000);
      off(i, device);
      usleep(10000);
    }
    destroy_color(color);
    destroy_blinkstick(device);
  }

  return 0;
}
