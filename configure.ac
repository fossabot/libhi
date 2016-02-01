AC_INIT([libhi], [0.0.1])
AM_INIT_AUTOMAKE([-Wall -Werror foreign subdir-objects])
AM_SILENT_RULES([yes])
AC_PROG_CC
AC_CONFIG_MACRO_DIRS([m4])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([
 Makefile
 src/Makefile
])
PKG_CHECK_MODULES_STATIC([GLFW3], [glfw3])

AM_PROG_AR
LT_INIT

AC_OUTPUT
