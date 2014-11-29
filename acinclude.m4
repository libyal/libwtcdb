dnl Function to detect if libwtcdb dependencies are available
AC_DEFUN([AX_LIBWTCDB_CHECK_LOCAL],
 [dnl Check for internationalization functions in libwtcdb/libwtcdb_i18n.c 
 AC_CHECK_FUNCS([bindtextdomain])
 ])

