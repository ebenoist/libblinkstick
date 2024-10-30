#ifndef _WINDOWS
#include <unistd.h>
#endif
#include "libblinkstick.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

typedef struct arguments arguments;
struct arguments;

struct arguments {
  int red;
  int green;
  int blue;
  int count;
  int index;
  int channel;
};

void usage() {
  printf("USAGE:\n\
  blinkstick [options...]\n\
OPTIONS\n\
  --color set the color using a three rgb values\n\
  --count set the number of blinkstick devices to address\n\
  --index which led should be set\n\
  --channel which channel to use (BlinkStick Pro)\n\
  --debug turn on debug logging\n");
}

struct arguments* parse_args(int argc, char** flags) {
  struct arguments* args = malloc(sizeof(arguments));
  args->count = 1;
  int color_set = 0;

  for (int i = 1; i < argc; i++) {
    if (flags[i] != NULL) {
      if (strcmp(flags[i], "--count") == 0) {
        args->count = atoi(*(flags + i + 1));
      }

      if (strcmp(flags[i], "--index") == 0) {
        args->index = atoi(*(flags + i + 1));
      }

	  if (strcmp(flags[i], "--channel") == 0) {
		  args->channel = atoi(*(flags + i + 1));
	  }

      if (strcmp(flags[i], "--debug") == 0) {
        blinkstick_debug();
      }

      if (strcmp(flags[i], "--color") == 0) {
        color_set = 1;
        args->red = atoi(*(flags + i + 1));
        args->green = atoi(*(flags + i + 2));
        args->blue = atoi(*(flags + i + 3));
      }

      if (strcmp(flags[i], "--help") == 0) {
        usage();
        exit(0);
      }
    }

    if (color_set == 0) {
      usage();
      exit(1);
    }
  }

  return args;
}

int main(int argc, char** argv) {
  struct arguments* args = parse_args(argc, argv);
  blinkstick_device** devices = blinkstick_find_many(args->count);

  for (int j = 0; j < args->count; j++) {
    // set the color
    blinkstick_set_color(devices[j], args->channel, args->index, args->red, args->green,
                         args->blue);
    // free the device
    blinkstick_destroy(devices[j]);
  }

  // possibly unecessary, but good practice nonetheless. 
  free(args);
  return 0;
}
