#include "libblinkstick.h"
#include "seatest.h"

void test_rgb_color_factory() {
  int red, green, blue;
  red = 1;
  green = 2;
  blue = 3;

  rgb_color *color = rgb_color_factory(red,green, blue);

  assert_true(color->red == red);
  assert_true(color->green == green);
  assert_true(color->blue == blue);
}

void test_byte_represenation() {
  int red, green, blue;
  red = 255;
  green = 255;
  blue = 255;

  rgb_color *color = rgb_color_factory(red,green, blue);
  assert_true((color->bytes != NULL));
}

void all_tests(void) {
  test_fixture_start();
  run_test(test_rgb_color_factory);
  run_test(test_byte_represenation);
  test_fixture_end();
}

int main(int argc, char** argv) {
  return run_tests(all_tests);
}
