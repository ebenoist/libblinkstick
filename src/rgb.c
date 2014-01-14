#include "rgb.h"

rgb_color* rgb_color_factory(int red, int green, int blue) {
  rgb_color *color = malloc(sizeof(rgb_color));

  color->red = red;
  color->green = green;
  color->blue = blue;
  color->hex = rgb_to_char(color);

  return color;
}

char * rgb_to_char(rgb_color *color) {
  char * hex = malloc(sizeof(char[255]));
  snprintf(hex, sizeof hex, "\\x%02x\\x%02x\\x%02x", color->red, color->green, color->blue);
  return hex;
}

