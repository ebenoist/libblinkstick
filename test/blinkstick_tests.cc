#include "gtest/gtest.h"

/* START_TEST (test_rgb_factory) { */
  /* int red, green, blue; */
  /* red = 1; */
  /* green = 2; */
  /* blue = 3; */

  /* rgb_color *color = rgb_color_factory(red,green, blue); */

  /* ck_assert(color->red == red); */
  /* ck_assert(color->green == green); */
  /* ck_assert(color->blue == blue); */
/* } */
/* END_TEST */

/* START_TEST (test_byte_representation) { */
  /* int red, green, blue; */
  /* red = 255; */
  /* green = 255; */
  /* blue = 255; */

  /* rgb_color *color = rgb_color_factory(red,green, blue); */
  /* ck_assert(color->bytes[0] == '\x01'); */
  /* ck_assert_msg(color->bytes[1] == 'ff', "Got: %2x", color->bytes[1]); */
/* } */
/* END_TEST */

TEST(SampleTest, AssertionTrue) {
  ASSERT_EQ(1,1);
}

