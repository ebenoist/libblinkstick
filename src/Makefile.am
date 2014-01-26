AUTOMAKE_OPTIONS = subdir-objects
ACLOCAL_AMFLAGS = ${ACLOCAL_FLAGS}

lib_LTLIBRARIES = lib@NAME@-@API_VERSION@.la

lib@NAME@_@API_VERSION@_la_SOURCES = libblinkstick.c rgb.c
lib@NAME@_@API_VERSION@_la_LDFLAGS = -version-info $(SO_VERSION)
lib@NAME@_@API_VERSION@_la_CFLAGS = $(LIBUSB_CFLAGS)
lib@NAME@_@API_VERSION@_la_LIBADD = $(LIBUSB_LIBS)
example_includedir = $(includedir)/
nobase_example_include_HEADERS = libblinkstick.h

## The generated configuration header is installed in its own subdirectory of
## $(libdir).  The reason for this is that the configuration information put
## into this header file describes the target platform the installed library
## has been built for.  Thus the file must not be installed into a location
## intended for architecture-independent files, as defined by the Filesystem
## Hierarchy Standard (FHS).
## The nodist_ prefix instructs Automake to not generate rules for including
## the listed files in the distribution on 'make dist'.  Files that are listed
## in _HEADERS variables are normally included in the distribution, but the
## configuration header file is generated at configure time and should not be
## shipped with the source tarball.
example_libincludedir = $(libdir)/@NAME@-$(API_VERSION)/include
nodist_example_libinclude_HEADERS = libblinkstick.h

## Define an independent executable script for inclusion in the distribution
## archive.  However, it will not be installed on an end user's system due to
## the noinst_ prefix.
dist_noinst_SCRIPTS = autogen.sh
