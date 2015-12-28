AC_INIT([libModeller],[0.1],[aykutblt@gmail.com])
AM_INIT_AUTOMAKE([foreign -Wall -Werror])
m4_ifdef([AM_PROG_AR], [AM_PROG_AR])
LT_INIT
LT_LANG([C++])
#LT_OUTPUT
AC_PREFIX_DEFAULT([`pwd`])
AC_PROG_CXX
AC_LANG(C++)
AX_CXX_COMPILE_STDCXX_11
#AC_PROG_RANLIB
#AM_PROG_AR
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([Makefile
	src/Makefile
	examples/Makefile
	modeller.pc
	modeller-uninstalled.pc])
AC_OUTPUT
