#include <libblinkstick.h>
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

  if (device) {
    set_color(color, device);
    sleep(2);
    off(device);
  }

  destroy_color(color);
  destroy_blinkstick(device);

  return 0;
}

