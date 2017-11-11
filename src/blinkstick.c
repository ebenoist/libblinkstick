#include <unistd.h>
#include "libblinkstick.h"

typedef struct arguments arguments;
struct arguments;

struct arguments {
  rgb_color* color;
  int count;
  int index;
};

struct arguments* parse_args(char** flags) {
  struct arguments* args = malloc(sizeof(arguments));

  for (int i = 1; i < sizeof(flags); i++) {
    if (flags[i] != NULL) {
      if (strcmp(flags[i], "--count") == 0) {
        args->count = atoi(*(flags + i + 1));
      }

      if (strcmp(flags[i], "--index") == 0) {
        args->index = atoi(*(flags + i + 1));
      }

      if (strcmp(flags[i], "--debug") == 0) {
        set_debug_true();
      }

      if (strcmp(flags[i], "--color") == 0) {
        char *red, *green, *blue;

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

  for (int j = 0; j < args->count; j++) {
    set_color(args->index, args->color, devices[j]);
    destroy_blinkstick(devices[j]);
  }

  destroy_color(args->color);
  return 0;
}
