AC_INIT([libquat], [1.0], [henrik@henrikmoller.me])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])
AC_PROG_CXX
AC_PROG_CXX_C_O
AC_PROG_LN_S
AC_CONFIG_HEADERS([config.h])
AM_MAINTAINER_MODE([enable])
AM_PROG_AR
LT_INIT



#AC_ARG_ENABLE([gcov],
#  [AS_HELP_STRING([--enable-gcov],
#    [use Gcov to test the test suite])],
#    [],
#    [enable_gcov=no])
#AM_CONDITIONAL([ENABLE_GCOV],[test '!' "$ENABLE_GCOV" = no])

AC_CONFIG_FILES([
  Makefile
  src/Makefile
])
AC_OUTPUT
