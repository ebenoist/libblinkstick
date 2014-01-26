AUTOMAKE_OPTIONS = subdir-objects
ACLOCAL_AMFLAGS = ${ACLOCAL_FLAGS}

LDADD = $(srcdir)../src/libblinkstick-0.1.la
AM_CPPFLAGS = -I$(srcdir)../src/libblinkstick.h -I$(srcdir)../src/rgb.h

bin_PROGRAMS = blinkstick
blinkstick_SOURCES = blinkstick.c

blinkstick_CFLAGS = $(LIBUSB_CFLAGS)
blinkstick_LDADD = $(LIBUSB_LIBS)


