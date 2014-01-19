#include "rgb.h"

rgb_color* rgb_color_factory(int red, int green, int blue) {
  rgb_color *color = malloc(sizeof(rgb_color));

  color->red = red;
  color->green = green;
  color->blue = blue;
  color->bytes = rgb_to_char(color);

  return color;
}

unsigned char * rgb_to_char(rgb_color *color) {
  unsigned char* bytes = malloc(sizeof(unsigned char[4]));
  bytes[0] = '\x01';
  bytes[1] = (color->red & 0xff);
  bytes[2] = (color->green & 0xff);
  bytes[3] = (color->blue & 0xff);

  return bytes;
}

void destroy_color(rgb_color *color) {
  free(color->bytes);
  free(color);
}

