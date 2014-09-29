AC_INIT([timer], [0.1.0], [yourmom@yourmom.com])

AC_CONFIG_HEADERS([config.h])
AC_CONFIG_AUX_DIR([config])
AC_CONFIG_MACRO_DIR([config])
AC_CONFIG_FILES([Makefile src/Makefile tests/Makefile])
AC_CONFIG_SRCDIR([src/timer.c])

AM_INIT_AUTOMAKE([foreign -Wall -Werror])

AC_PROG_LIBTOOL
LT_INIT

AC_PROG_CC
AM_PROG_CC_C_O
m4_pattern_allow([AM_PROG_AR],[AM_PROG_AR])
AM_PROG_AR

AC_ARG_ENABLE(all-static,
        [AS_HELP_STRING([--enable-all-static],[add '-all-static' during libtool linking to force all static libraries and linking (default: no)])],
        [if test "$enableval" = "yes" ; then
	AC_SUBST([CCLD],['$(CC) -all-static'])
	else
	AC_SUBST([CCLD],['$(CC)'])
        fi],
	[AC_SUBST([CCLD],['$(CC)'])])


AC_OUTPUT

