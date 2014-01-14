#include <stdio.h>
#include <stdlib.h>

struct rgb_color;
typedef struct rgb_color rgb_color;

struct rgb_color {
  int red;
  int green;
  int blue;
  char * hex;
};

rgb_color* rgb_color_factory(int red, int green, int blue);
char * rgb_to_char(rgb_color *color);
