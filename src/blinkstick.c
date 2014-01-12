#include "libblinkstick.h"

void parse_args(char **flags) {
  char * first_flag = flags[1];

  if(first_flag != NULL) {
    if ((strcmp(first_flag, "--debug")) || (strcmp(first_flag, "-d"))) {
      set_debug_true();
    }
  }
}

int main(int argc, char **argv) {
  parse_args(argv);
  blinkstick_device *device = find_blinkstick();

  if (device) {
    printf("Woah!\n");
  }

  free(device);
  return 0;
}

