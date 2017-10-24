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
  int number_of_devices = 1;
  blinkstick_device_list *devices = blinkstick_list_factory(number_of_devices);

  find_blinkstick(devices);

  int i, j;
  for(i = 0; i < number_of_devices; i++)
  {
    if(devices->blinkstick_device_list[i] != NULL)
    {
      for(j = 0; j < 8; j++)
      {
        set_color(j, color, devices->blinkstick_device_list[i]);
        usleep(1000);
        off(j, devices->blinkstick_device_list[i]);
        usleep(1000);
      }
    }
  }
  destroy_color(color);
  destroy_blinkstick(devices);

  return 0;
}
