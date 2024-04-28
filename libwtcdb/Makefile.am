AM_CPPFLAGS = \
	-I../include -I$(top_srcdir)/include \
	-I../common -I$(top_srcdir)/common \
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
	@LIBWTCDB_DLL_EXPORT@

lib_LTLIBRARIES = libwtcdb.la

libwtcdb_la_SOURCES = \
	libwtcdb.c \
	libwtcdb_cache_entry.c libwtcdb_cache_entry.h \
	libwtcdb_crc.c libwtcdb_crc.h \
	libwtcdb_debug.c libwtcdb_debug.h \
	libwtcdb_definitions.h \
	libwtcdb_error.c libwtcdb_error.h \
	libwtcdb_extern.h \
	libwtcdb_file.c libwtcdb_file.h \
	libwtcdb_file_header.c libwtcdb_file_header.h \
	libwtcdb_index_entry.c libwtcdb_index_entry.h \
	libwtcdb_io_handle.c libwtcdb_io_handle.h \
	libwtcdb_item.c libwtcdb_item.h \
	libwtcdb_libbfio.h \
	libwtcdb_libcdata.h \
	libwtcdb_libcerror.h \
	libwtcdb_libclocale.h \
	libwtcdb_libcnotify.h \
	libwtcdb_libfdatetime.h \
	libwtcdb_libuna.h \
	libwtcdb_notify.c libwtcdb_notify.h \
	libwtcdb_support.c libwtcdb_support.h \
	libwtcdb_types.h \
	libwtcdb_unused.h \
	wtcdb_cache_entry.h \
	wtcdb_file_header.h \
	wtcdb_index_entry.h

libwtcdb_la_LIBADD = \
	@LIBCERROR_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBBFIO_LIBADD@ \
	@LIBFDATETIME_LIBADD@

libwtcdb_la_LDFLAGS = -no-undefined -version-info 1:0:0

EXTRA_DIST = \
	libwtcdb_definitions.h.in \
	libwtcdb.rc \
	libwtcdb.rc.in

DISTCLEANFILES = \
	libwtcdb_definitions.h \
	libwtcdb.rc \
	Makefile \
	Makefile.in

sources-local: $(BUILT_SOURCES)

splint-local:
	@echo "Running splint on libwtcdb ..."
	-splint -preproc -redef $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(libwtcdb_la_SOURCES)

