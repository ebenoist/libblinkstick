AUTOMAKE_OPTIONS = subdir-objects
ACLOCAL_AMFLAGS = ${ACLOCAL_FLAGS}

TESTS = blinkstick_tests
check_PROGRAMS = blinkstick_tests
blinkstick_tests_SOURCES = blinkstick_tests.c $(top_builddir)/src/libblinkstick.h
blinkstick_tests_CFLAGS = @CHECK_CFLAGS@ $(LIBUSB_CFLAGS)
blinkstick_tests_LDADD = $(top_builddir)/src/libblinkstick-0.1.la @CHECK_LIBS@ $(LIBUSB_LIBS)


