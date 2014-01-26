AUTOMAKE_OPTIONS = subdir-objects
ACLOCAL_AMFLAGS = ${ACLOCAL_FLAGS}

TESTS = blinkstick_tests
check_PROGRAMS = blinkstick_tests
blinkstick_tests_SOURCES = blinkstick_tests.c
blinkstick_tests_CFLAGS = @CHECK_CFLAGS@ $(LIBUSB_CFLAGS)
blinkstick_tests_LDADD = @CHECK_LIBS@ $(LIBUSB_LIBS) -L../src/ -llibblinkstick



