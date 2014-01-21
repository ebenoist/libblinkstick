AC_INIT([libblinkstick], [0.1], [ebenoist@gmail.com])
AC_PREREQ([2.59])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])

AM_PROG_AR
LT_INIT
AC_PROG_CC

AC_SUBST([NAME], "libblinkstick")
AC_SUBST([API_VERSION], ["0.1"])
AC_SUBST([SO_VERSION], ["0:1:0"])

PKG_CHECK_MODULES([LIBUSB], [libusb-1.0 >= 1.0])

# Override the template file name of the generated .pc file, so that there
# is no need to rename the template file when the API version changes.
AC_CONFIG_FILES([Makefile src/Makefile
                 libblinkstick-${API_VERSION}.pc:libblinkstick.pc.in])

AC_OUTPUT
