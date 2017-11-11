#include <unistd.h>
#include "libblinkstick.h"

struct arguments* parse_args(char** flags) {
  struct arguments* args = malloc(sizeof(arguments));

  for (int i = 1; i < sizeof(flags); i++) {
    if (flags[i] != NULL) {
      if (strcmp(flags[i], "--count") == 0) {
        args->count = atoi(*(flags + i + 1));
      }

      if (strcmp(flags[i], "--debug") == 0) {
        set_debug_true();
      }

      if (strcmp(flags[i], "--color") == 0) {
        char *red, *green, *blue;

        // sloppy
        red = *(flags + i + 1);
        green = *(flags + i + 2);
        blue = *(flags + i + 3);

        args->color = rgb_color_factory(atoi(red), atoi(green), atoi(blue));
      }
    }
  }

  return args;
}

int main(int argc, char** argv) {
  struct arguments* args = parse_args(argv);
  blinkstick_device** devices = find_blinksticks(args->count);

  int j;
  for (j = 0; j < args->count; j++) {
    int i;
    for (i = 0; i < 8; i++) {
      set_color(i, args->color, devices[j]);
      usleep(10000);
      off(i, devices[j]);
      usleep(10000);
    }
    destroy_blinkstick(devices[j]);
  }

  destroy_color(args->color);
  return 0;
}
