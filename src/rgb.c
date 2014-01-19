#include "rgb.h"

rgb_color* rgb_color_factory(int red, int green, int blue) {
  rgb_color *color = malloc(sizeof(rgb_color));

  color->red = red;
  color->green = green;
  color->blue = blue;
  color->bytes = rgb_to_char(color);

  return color;
}

char * rgb_to_char(rgb_color *color) {
  char* bytes = malloc(sizeof(char[4]));
  bytes[0] = '\x01';
  bytes[1] = (char)(color->red & 0xFF);
  bytes[2] = (char)(color->green & 0xFF);
  bytes[3] = (char)(color->blue & 0xFF);
  return bytes;
}

