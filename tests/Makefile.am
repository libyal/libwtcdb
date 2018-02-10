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
	@LIBFDATETIME_CPPFLAGS@ \
	@LIBWTCDB_DLL_IMPORT@

TESTS = \
	test_library.sh \
	test_wtcdbexport.sh \
	test_wtcdbinfo.sh

check_SCRIPTS = \
	test_library.sh \
	test_runner.sh \
	test_wtcdbexport.sh \
	test_wtcdbinfo.sh

EXTRA_DIST = \
	$(check_SCRIPTS)

check_PROGRAMS = \
	wtcdb_test_cache_entry \
	wtcdb_test_crc \
	wtcdb_test_error \
	wtcdb_test_file \
	wtcdb_test_file_header \
	wtcdb_test_index_entry \
	wtcdb_test_io_handle \
	wtcdb_test_item \
	wtcdb_test_notify \
	wtcdb_test_support

wtcdb_test_cache_entry_SOURCES = \
	wtcdb_test_cache_entry.c \
	wtcdb_test_libcerror.h \
	wtcdb_test_libwtcdb.h \
	wtcdb_test_macros.h \
	wtcdb_test_memory.c wtcdb_test_memory.h \
	wtcdb_test_unused.h

wtcdb_test_cache_entry_LDADD = \
	../libwtcdb/libwtcdb.la \
	@LIBCERROR_LIBADD@

wtcdb_test_crc_SOURCES = \
	wtcdb_test_crc.c \
	wtcdb_test_libcerror.h \
	wtcdb_test_libwtcdb.h \
	wtcdb_test_macros.h \
	wtcdb_test_unused.h

wtcdb_test_crc_LDADD = \
	../libwtcdb/libwtcdb.la \
	@LIBCERROR_LIBADD@

wtcdb_test_error_SOURCES = \
	wtcdb_test_error.c \
	wtcdb_test_libwtcdb.h \
	wtcdb_test_macros.h \
	wtcdb_test_unused.h

wtcdb_test_error_LDADD = \
	../libwtcdb/libwtcdb.la

wtcdb_test_file_SOURCES = \
	wtcdb_test_file.c \
	wtcdb_test_functions.c wtcdb_test_functions.h \
	wtcdb_test_getopt.c wtcdb_test_getopt.h \
	wtcdb_test_libbfio.h \
	wtcdb_test_libcerror.h \
	wtcdb_test_libclocale.h \
	wtcdb_test_libcnotify.h \
	wtcdb_test_libuna.h \
	wtcdb_test_libwtcdb.h \
	wtcdb_test_macros.h \
	wtcdb_test_memory.c wtcdb_test_memory.h \
	wtcdb_test_unused.h

wtcdb_test_file_LDADD = \
	@LIBBFIO_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	../libwtcdb/libwtcdb.la \
	@LIBCTHREADS_LIBADD@ \
	@LIBCERROR_LIBADD@ \
	@PTHREAD_LIBADD@

wtcdb_test_file_header_SOURCES = \
	wtcdb_test_file_header.c \
	wtcdb_test_libcerror.h \
	wtcdb_test_libwtcdb.h \
	wtcdb_test_macros.h \
	wtcdb_test_memory.c wtcdb_test_memory.h \
	wtcdb_test_unused.h

wtcdb_test_file_header_LDADD = \
	../libwtcdb/libwtcdb.la \
	@LIBCERROR_LIBADD@

wtcdb_test_index_entry_SOURCES = \
	wtcdb_test_index_entry.c \
	wtcdb_test_libcerror.h \
	wtcdb_test_libwtcdb.h \
	wtcdb_test_macros.h \
	wtcdb_test_memory.c wtcdb_test_memory.h \
	wtcdb_test_unused.h

wtcdb_test_index_entry_LDADD = \
	../libwtcdb/libwtcdb.la \
	@LIBCERROR_LIBADD@

wtcdb_test_io_handle_SOURCES = \
	wtcdb_test_io_handle.c \
	wtcdb_test_libcerror.h \
	wtcdb_test_libwtcdb.h \
	wtcdb_test_macros.h \
	wtcdb_test_memory.c wtcdb_test_memory.h \
	wtcdb_test_unused.h

wtcdb_test_io_handle_LDADD = \
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

wtcdb_test_notify_SOURCES = \
	wtcdb_test_libwtcdb.h \
	wtcdb_test_macros.h \
	wtcdb_test_notify.c \
	wtcdb_test_unused.h

wtcdb_test_notify_LDADD = \
	../libwtcdb/libwtcdb.la

wtcdb_test_support_SOURCES = \
	wtcdb_test_functions.c wtcdb_test_functions.h \
	wtcdb_test_getopt.c wtcdb_test_getopt.h \
	wtcdb_test_libbfio.h \
	wtcdb_test_libcerror.h \
	wtcdb_test_libclocale.h \
	wtcdb_test_libcnotify.h \
	wtcdb_test_libuna.h \
	wtcdb_test_libwtcdb.h \
	wtcdb_test_macros.h \
	wtcdb_test_support.c \
	wtcdb_test_unused.h

wtcdb_test_support_LDADD = \
	@LIBBFIO_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	../libwtcdb/libwtcdb.la \
	@LIBCERROR_LIBADD@

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f Makefile

