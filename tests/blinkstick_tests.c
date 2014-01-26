#include <check.h>
#include <stdio.h>
#include "../src/libblinkstick.h"

START_TEST (test_rgb_factory) {
  int red, green, blue;
  red = 1;
  green = 2;
  blue = 3;

  rgb_color *color = rgb_color_factory(red,green, blue);

  ck_assert(color->red == red);
  ck_assert(color->green == green);
  ck_assert(color->blue == blue);
}
END_TEST

Suite * basic_suite (void) {
  Suite *s = suite_create ("Lib BlinkStick");

  /* Core test case */
  TCase *tc_core = tcase_create ("Core");
  tcase_add_test (tc_core, test_rgb_factory);
  suite_add_tcase (s, tc_core);

  return s;
}

int main (void) {
  int number_failed;
  Suite *s = basic_suite ();
  SRunner *sr = srunner_create (s);
  srunner_run_all (sr, CK_NORMAL);
  number_failed = srunner_ntests_failed (sr);
  srunner_free (sr);
  return (number_failed == 0) ? 0 : 1;
}


