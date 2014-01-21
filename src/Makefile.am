AUTOMAKE_OPTIONS = subdir-objects
ACLOCAL_AMFLAGS = ${ACLOCAL_FLAGS}

lib_LTLIBRARIES = libblinkstick-@API_VERSION@.la

## Define the source file list for the "libexample-@API_VERSION@.la"
## target.  Note that @API_VERSION@ is not interpreted by Automake and
## will therefore be treated as if it were literally part of the target name,
## and the variable name derived from that.
## The file extension .cc is recognized by Automake, and makes it produce
## rules which invoke the C++ compiler to produce a libtool object file (.lo)
## from each source file.  Note that it is not necessary to list header files
## which are already listed elsewhere in a _HEADERS variable assignment.
libblinkstick_@API_VERSION@_la_SOURCES = libblinkstick.c rgb.c

## Instruct libtool to include ABI version information in the generated shared
## library file (.so).  The library ABI version is defined in configure.ac, so
## that all version information is kept in one place.
libblinkstick_@API_VERSION@_la_LDFLAGS = -version-info $(SO_VERSION)
libblinkstick_@API_VERSION@_la_CFLAGS = $(LIBUSB_CFLAGS)
libblinkstick_@API_VERSION@_la_LIBADD = $(LIBUSB_LIBS)

## Define the list of public header files and their install location.  The
## nobase_ prefix instructs Automake to not strip the directory part from each
## filename, in order to avoid the need to define separate file lists for each
## installation directory.  This only works if the directory hierarchy in the
## source tree matches the hierarchy at the install location, however.
example_includedir = $(includedir)/src-$(API_VERSION)
nobase_example_include_HEADERS = rgb.h libblinkstick.h

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
example_libincludedir = $(libdir)/libblinkstick-$(API_VERSION)/include
nodist_example_libinclude_HEADERS = libblinkstick.h

## Define an independent executable script for inclusion in the distribution
## archive.  However, it will not be installed on an end user's system due to
## the noinst_ prefix.
dist_noinst_SCRIPTS = autogen.sh
