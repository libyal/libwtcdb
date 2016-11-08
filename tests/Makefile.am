AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
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
	test_api_types.sh \
	test_wtcdbinfo.sh \
	test_wtcdbexport.sh

check_SCRIPTS = \
	test_api_functions.sh \
	test_api_types.sh \
	test_runner.sh \
	test_wtcdbexport.sh \
	test_wtcdbinfo.sh

EXTRA_DIST = \
	$(check_SCRIPTS)

check_PROGRAMS = \
	wtcdb_test_error \
	wtcdb_test_file \
	wtcdb_test_item \
	wtcdb_test_support

wtcdb_test_error_SOURCES = \
	wtcdb_test_error.c \
	wtcdb_test_libwtcdb.h \
	wtcdb_test_macros.h \
	wtcdb_test_unused.h

wtcdb_test_error_LDADD = \
	../libwtcdb/libwtcdb.la

wtcdb_test_file_SOURCES = \
	wtcdb_test_file.c \
	wtcdb_test_libcerror.h \
	wtcdb_test_libclocale.h \
	wtcdb_test_libcsystem.h \
	wtcdb_test_libwtcdb.h \
	wtcdb_test_libuna.h \
	wtcdb_test_memory.c wtcdb_test_memory.h \
	wtcdb_test_unused.h

wtcdb_test_file_LDADD = \
	@LIBCSYSTEM_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	../libwtcdb/libwtcdb.la \
	@LIBCERROR_LIBADD@

wtcdb_test_item_SOURCES = \
	wtcdb_test_item.c \
	wtcdb_test_libcerror.h \
	wtcdb_test_libwtcdb.h \
	wtcdb_test_macros.h \
	wtcdb_test_memory.c wtcdb_test_memory.h \
	wtcdb_test_unused.h

wtcdb_test_item_LDADD = \
	../libwtcdb/libwtcdb.la \
	@LIBCERROR_LIBADD@

wtcdb_test_support_SOURCES = \
	wtcdb_test_libcerror.h \
	wtcdb_test_libclocale.h \
	wtcdb_test_libcsystem.h \
	wtcdb_test_libwtcdb.h \
	wtcdb_test_libuna.h \
	wtcdb_test_macros.h \
	wtcdb_test_support.c \
	wtcdb_test_unused.h

wtcdb_test_support_LDADD = \
	@LIBCSYSTEM_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	../libwtcdb/libwtcdb.la \
	@LIBCERROR_LIBADD@

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f Makefile

