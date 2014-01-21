#include <stdio.h>
#include <stdlib.h>

struct rgb_color;
typedef struct rgb_color rgb_color;

struct rgb_color {
  int red;
  int green;
  int blue;
  unsigned char * bytes;
};

rgb_color* rgb_color_factory(int red, int green, int blue);
unsigned char *rgb_to_char(rgb_color *color);
void destroy_color(rgb_color *color);
