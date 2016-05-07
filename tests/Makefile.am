AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	@LIBCSTRING_CPPFLAGS@ \
	@LIBCERROR_CPPFLAGS@ \
	@LIBCDATA_CPPFLAGS@ \
	@LIBCLOCALE_CPPFLAGS@ \
	@LIBCNOTIFY_CPPFLAGS@ \
	@LIBCSPLIT_CPPFLAGS@ \
	@LIBUNA_CPPFLAGS@ \
	@LIBCFILE_CPPFLAGS@ \
	@LIBCPATH_CPPFLAGS@ \
	@LIBBFIO_CPPFLAGS@ \
	@LIBCSYSTEM_CPPFLAGS@ \
	@PTHREAD_CPPFLAGS@ \
	@LIBWTCDB_DLL_IMPORT@

TESTS = \
	test_api_functions.sh \
	test_wtcdbinfo.sh \
	test_wtcdbexport.sh

check_SCRIPTS = \
	test_api_functions.sh \
	test_runner.sh \
	test_wtcdbexport.sh \
	test_wtcdbinfo.sh

EXTRA_DIST = \
	$(check_SCRIPTS)

check_PROGRAMS = \
	wtcdb_test_get_version \
	wtcdb_test_open_close

wtcdb_test_get_version_SOURCES = \
	wtcdb_test_get_version.c \
	wtcdb_test_libcstring.h \
	wtcdb_test_libwtcdb.h \
	wtcdb_test_unused.h

wtcdb_test_get_version_LDADD = \
	../libwtcdb/libwtcdb.la \
	@LIBCSTRING_LIBADD@

wtcdb_test_open_close_SOURCES = \
	wtcdb_test_libcerror.h \
	wtcdb_test_libcstring.h \
	wtcdb_test_libcsystem.h \
	wtcdb_test_libwtcdb.h \
	wtcdb_test_open_close.c

wtcdb_test_open_close_LDADD = \
	@LIBCSYSTEM_LIBADD@ \
	../libwtcdb/libwtcdb.la \
	@LIBCTHREADS_LIBADD@ \
	@LIBCERROR_LIBADD@ \
	@LIBCSTRING_LIBADD@ \
	@PTHREAD_LIBADD@

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f Makefile

