AUTOMAKE_OPTIONS = subdir-objects
ACLOCAL_AMFLAGS = ${ACLOCAL_FLAGS}

TESTS = blinkstick_tests.o
check_PROGRAMS = blinkstick_tests.o
blinkstick_tests_SOURCES = minunit.h libblinkstick_test.c
blinkstick_tests_CFLAGS = @CHECK_CFLAGS@
blinkstick_tests_LDADD = @CHECK_LIBS@


