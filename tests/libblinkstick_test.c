#include <check.h>
#include <stdio.h>

START_TEST (test_some)
{
  ck_assert( 0 == 0 );
}
END_TEST

Suite * basic_suite (void)
{
  Suite *s = suite_create ("Lib BlinkStick");

  /* Core test case */
  TCase *tc_core = tcase_create ("Core");
  tcase_add_test (tc_core, test_some);
  suite_add_tcase (s, tc_core);

  return s;
}

int main (void)
{
  int number_failed;
  Suite *s = basic_suite ();
  SRunner *sr = srunner_create (s);
  srunner_run_all (sr, CK_NORMAL);
  number_failed = srunner_ntests_failed (sr);
  srunner_free (sr);
  return (number_failed == 0) ? 0 : 1;
}


